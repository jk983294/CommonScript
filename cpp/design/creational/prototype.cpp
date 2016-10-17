#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

/**
 * Problem
 * when the type of objects to create is determined by a prototypical instance, which is cloned to produce new objects.
 * Solution
 * Declare an abstract base class that specifies a pure virtual clone() method.
 * Any class that needs a "polymorphic constructor" capability derives itself from the abstract base class,
 * and implements the clone() operation.
 */

class Record
{
public:
    virtual ~Record() {}
    virtual void print() = 0;
    virtual unique_ptr<Record> clone() = 0;
};

class CarRecord : public Record
{
private:
    string m_carName;
    int m_ID;

public:
    CarRecord(string carName, int ID) : m_carName(carName), m_ID(ID)
    {
    }

    void print() override
    {
        cout << "Car Record" << endl
        << "Name  : "   << m_carName << endl
        << "Number: "   << m_ID << endl << endl;
    }

    unique_ptr<Record> clone() override
    {
        return unique_ptr<CarRecord>(new CarRecord(*this));
    }
};

class BikeRecord : public Record
{
private:
    string m_bikeName;
    int m_ID;

public:
    BikeRecord(string bikeName, int ID) : m_bikeName(bikeName), m_ID(ID)
    {
    }

    void print() override
    {
        cout << "Bike Record" << endl
        << "Name  : " << m_bikeName << endl
        << "Number: " << m_ID << endl << endl;
    }

    unique_ptr<Record> clone() override
    {
        return unique_ptr<BikeRecord>(new BikeRecord(*this));
    }
};

class PersonRecord : public Record
{
private:
    string m_personName;
    int m_age;

public:
    PersonRecord(string personName, int age) : m_personName(personName), m_age(age)
    {
    }

    void print() override
    {
        cout << "Person Record" << endl
        << "Name : " << m_personName << endl
        << "Age  : " << m_age << endl << endl;
    }

    unique_ptr<Record> clone() override
    {
        return unique_ptr<PersonRecord>(new PersonRecord(*this));
    }
};

enum RecordType
{
    CAR,
    BIKE,
    PERSON
};

class RecordFactory
{
private:
    unordered_map<RecordType, unique_ptr<Record>, hash<int> > m_records;

public:
    RecordFactory()
    {
        m_records[CAR]    = unique_ptr<CarRecord>(new CarRecord("Ferrari", 5050));
        m_records[BIKE]   = unique_ptr<BikeRecord>(new BikeRecord("Yamaha", 2525));
        m_records[PERSON] = unique_ptr<PersonRecord>(new PersonRecord("Tom", 25));
    }

    unique_ptr<Record> createRecord(RecordType recordType)
    {
        return m_records[recordType]->clone();
    }
};

int main()
{
    RecordFactory recordFactory;

    auto record = recordFactory.createRecord(CAR);
    record->print();

    record = recordFactory.createRecord(BIKE);
    record->print();

    record = recordFactory.createRecord(PERSON);
    record->print();
    return 0;
}