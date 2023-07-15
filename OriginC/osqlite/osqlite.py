"""
This module contains tools for interacting with SQLite databases representing OriginLab workbooks.
"""

import pandas as pd
import pathlib
import sqlite3
import numpy as np


class OSQLFile:
    """Read/Write SQLite files that interop with OriginLab workbooks"""

    def __init__(self, sqlite_file_path: str):
        self.path = pathlib.Path(sqlite_file_path)
        if not self.path.is_file():
            raise Exception(f"File does not exist: {self.path}")

    def _query_strings(self, query: str) -> list[str]:
        con = sqlite3.connect(self.path)
        cursor = con.cursor()
        cursor.execute(query)
        strings = [x[0] for x in cursor.fetchall()]
        con.close()
        return strings

    def get_column_names(self, sheet_name: str = None):
        """Return column names for the given sheet."""
        query = f"SELECT name FROM PRAGMA_TABLE_INFO('{sheet_name}')"
        return (self._query_strings(query))

    def get_column_values(self, sheet_name: str, column_name: str):
        query = f'SELECT "{column_name}" FROM "{sheet_name}"'
        values = self._query_strings(query)
        values = np.array(values)
        return values

    def get_sheet_np(self, sheet_name: str) -> np.ndarray:
        """Return sheet data values as a numpy array."""
        query = f"SELECT * FROM '{sheet_name}'"
        con = sqlite3.connect(self.path)
        cursor = con.cursor()
        cursor.execute(query)
        rows = [x for x in cursor.fetchall()]
        con.close()

        width = max([len(x) for x in rows])
        height = len(rows)
        data = np.empty((height, width)) * np.nan

        for i, row in enumerate(rows):
            data[i, :len(row)] = row

        return data

    def get_sheet_df(self, sheet_name: str) -> pd.DataFrame:
        """Return sheet data as Pandas DataFrame."""
        data = self.get_sheet_np(sheet_name)
        column_names = self.get_column_names(sheet_name)
        return pd.DataFrame(data, columns=column_names)

    def get_sheet_names(self, name_match: str = None) -> list[str]:
        """Return names for all sheets in the book."""
        query = "SELECT name FROM sqlite_master WHERE type='table'"
        sheet_names = self._query_strings(query)
        if name_match:
            sheet_names = [x for x in sheet_names if name_match in x]
        return sheet_names

    def add_sheet(self, sheet_name: str, df: pd.DataFrame, overwrite: bool = True):
        """Add a worksheet from a Pandas DataFrame."""
        con = sqlite3.connect(self.path)

        if overwrite:
            query = f"DROP TABLE IF EXISTS '{sheet_name}'"
            cursor = con.cursor()
            cursor.execute(query)

        column_names_and_types = ", ".join([f"'{x}' REAL" for x in df.columns])
        query = f"CREATE TABLE IF NOT EXISTS '{sheet_name}' ({column_names_and_types})"
        con = sqlite3.connect(self.path)
        cursor = con.cursor()
        cursor.execute(query)

        # TODO: make this a transaction to improve performance
        data = df.to_numpy()
        for i in range(data.shape[0]):
            values = ", ".join([str(int(x)) for x in data[i]])
            query = f"INSERT INTO '{sheet_name}' VALUES ({values})"
            cursor.execute(query)

        con.commit()
        con.close()

    def getcols(self, column_index: int, name_match: str = None):
        """Return a Pandas DataFrame containing the Nth column from every sheet."""
        sheet_names = self.get_sheet_names(name_match)

        values_by_column = []
        for sheet_name in sheet_names:
            column_names = self.get_column_names(sheet_name)
            column_name = column_names[column_index]
            column_values = self.get_column_values(sheet_name, column_name)
            values_by_column.append(column_values)

        column_count = len(sheet_names)
        row_count = max([len(x) for x in values_by_column])
        data = np.empty((row_count, column_count)) * np.nan
        for i, values in enumerate(values_by_column):
            data[:len(values), i] = values

        df = pd.DataFrame(data, columns=sheet_names)
        return df
