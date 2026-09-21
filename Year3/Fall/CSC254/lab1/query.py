import psycopg2

connect = psycopg2.connect(host="localhost",
            database="postgres",
            user="postgres",
            password="WigWomm$24",
            port="5432"
        )

cursor = connect.cursor()


cursor.execute("SELECT * FROM Jams")
records = cursor.fetchall()
for i in records:
    print(i)


connect.commit()
cursor.close()
connect.close()
