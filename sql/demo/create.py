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

if __name__=="__main__":
    with open (R"X:\Data\surgeries\surgery_log.csv") as f:
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
        rows.append(fields)
        keys=list(fields.keys())
        values=list(fields.values())
        for i,val in enumerate(values):
            if type(val)==int:
                val=str(val)
            elif len(val)==0:
                val='NULL'
            else:
                val="`%s`"%val
            print(val)
        #sqlIns="INSERT INTO `animals` ()"
        #print(sql)
        print()
    print("DONE")
