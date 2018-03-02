"""
This script reads the surgery log (CSV) and creates a SQLite3 database (clearing what was there).

id,animal,originalCage,gender,genotype,target,substance,volume,coords,dateSx,dateSac,notes

CREATE TABLE "animals" ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
                        `animal` TEXT NOT NULL, `originalCage` TEXT, `gender` NUMERIC,
                        `genotype` NUMERIC, `target` TEXT, `substance` TEXT, `volume` TEXT,
                        `coords` TEXT, `dateSx` TEXT, `dateSac` TEXT, `notes` TEXT, `hidden` INTEGER );

INSERT INTO `animals` (`id`,`animal`,`originalCage`,`gender`,`genotype`,`target`,`substance`,
                       `volume`,`coords`,`dateSx`,`dateSac`,`notes`, `hidden`)
       VALUES (12,'',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);

"""



import collections
import os
import sqlite3

def csvToTable(fname="surgery_log.csv"):
    with open (os.path.join(fname)) as f:
        raw=f.read().split("\n")
    rows=[]
    for line in raw:
        if not len(line)>20: continue
        line=line.split(",")
        fields=collections.OrderedDict()
        fields["id"]=len(rows)
        fields["animal"]=line[0]
        fields["originalCage"]=line[1]
        fields["gender"]="M"
        fields["genotype"]=line[2]
        fields["target"]=line[3]
        fields["substance"]=line[4]
        fields["volume"]=line[5]
        fields["coords"]=line[6]+","+line[7]+","+line[8]
        fields["dateSx"]=line[9]
        fields["dateSac"]=line[10]
        fields["notes"]=line[12]
        fields["hidden"]=0
        keys=list(fields.keys())
        values=list(fields.values())
        for i,val in enumerate(values):
            if type(val)==int:
                values[i]=str(val)
            elif len(val.strip())==0:
                values[i]='NULL'
            else:
                values[i]="`%s`"%val
        rows.append([keys,values])
    return rows

def sqlInsertRow(row):
    sqlKey,sqlVal=[],[]
    for i in range(len(row[0])):
        key,val=row[0][i],row[1][i]
        sqlKey.append("`%s`"%key)
        sqlVal.append(str(val))
    sql="INSERT INTO `animals` (%s) \nVALUES (%s);"%(", ".join(sqlKey),", ".join(sqlVal))
    return sql

if __name__=="__main__":
    # load data from the CSV file
    rows=csvToTable()

    # create an empty database    
    conn = sqlite3.connect(r"surgeries.db")
    c = conn.cursor()
    c.execute("DROP TABLE `animals`") # delete the old data

    # create the database structure
    sql="""
        CREATE TABLE "animals" ( `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
                                `animal` TEXT NOT NULL, `originalCage` TEXT, `gender` NUMERIC,
                                `genotype` NUMERIC, `target` TEXT, `substance` TEXT, `volume` TEXT,
                                `coords` TEXT, `dateSx` TEXT, `dateSac` TEXT, `notes` TEXT, `hidden` INTEGER );
        """
    c.execute(sql.strip())

    # copy CSV data into the new database
    for row in rows:
        sql=sqlInsertRow(row)
        sql=sql.replace("`","'")
        print(sql)
        conn.execute(sql)
    print("DONE")

    # save database to disk
    conn.commit()
    conn.close()
    print("DONE")