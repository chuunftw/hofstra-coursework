import psycopg2

connect = psycopg2.connect(
    host="localhost",
    database="studentgpa",
    user="postgres",
    password="WigWomm$24",
    port="5432"
)

cursor = connect.cursor()

# Use the SQL query that calculates GPA from grades table
cursor.execute("SELECT * FROM students")

gpa = cursor.fetchall()


print("----------------------------------------")
for i in gpa:
    student_name, student_id, gpa = i
    print(f"Student Name: {student_name}")
    print(f"Student ID:   {student_id}")
    print(f"GPA:          {gpa}")
    print("----------------------------------------")


cursor.close()
connect.close()