class Student{
  public:

	Student();

    void readStudent();

    void displayStudent();

    int getAge();

    void setAge(short age);

private:

    char fname[20];
    char lname[20];
    short age;
    short gradYear;
    int id;

};
