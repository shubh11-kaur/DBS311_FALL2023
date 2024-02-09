/*
			GROUP 14
Luckshihaa Krishnan  -186418216
Shubhdeep kaur – 172915217
Gayatri Sharma – 174241216
*/

#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// Luckshishaa's table
class Electricity {
public:
	int suiteid = 0;
	int resid = 0;
	string date = "";
	double amount = 0.0;
	int banknumber = 0;
};

//shubh's table :

class Residents {
public:

	int residentid = 0;

	string firstname = "";

	string lastname = "";

	int suitenumber = 0;

	string phonenumber = "";
};

//Gayatri's table

class Packages {
public:
	int residentid = 0;
	string residentname = "";
	int suitenumber = 0;
	string packagedetails = "";
	string deliveredby = "";
};

int main(void) {

	//OCCI VARIABLES
	Environment* env = nullptr;
	Connection* conn = nullptr;

	//User Variables
	string str;

	//Luckshihaa Krishnan - LOGIN
	string usr = "dbs311_233nbb09";
	string pass = "27219488";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	//Shubhdeep Kaur - LOGIN
	//string usr = ;
	//string pass = ;
	//string srv = ;

	//Gayatri Sharma - LOGIN
	//string usr = ;
	//string pass = ;
	//string srv = ;

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		int input;
		bool ok = true;

		do {
			cout << "--- HIGH RAISE CONDO MAINTENANCE ---" << endl;
			cout << "1) Create an Electricity entry" << endl;	//luckshihaa's table
			cout << "2) Update an Electricity entry" << endl;	//luckshihaa's table
			cout << "3) Delete an Electricity entry" << endl;	//luckshihaa's table
			cout << "4) Read an Electricity entry" << endl;		//luckshihaa's table

			cout << "5) Create a Residents entry" << endl;		//shubhdeep's table
			cout << "6) Update a Residents entry" << endl;		//shubhdeep's table
			cout << "7) Delete a Residents entry" << endl;		//shubhdeep's table
			cout << "8) Read a Residents entry" << endl;			//shubhdeep's table

			cout << "9) Create a Package entry" << endl;			//gayatri's table
			cout << "10) Update a Package entry" << endl;		//gayatri's table
			cout << "11) Delete a Package entry" << endl;		//gayatri's table
			cout << "12) Read a Package entry" << endl;			//gayatri's table

			cout << "0) Exit" << endl;
			cout << "Enter an option (0-12): ";
			cin >> input;

			if (input == 1) {
				ok = true;
				int err = 0;
				Electricity elec;
				cout << "Enter Suite ID: ";
				cin >> elec.suiteid;
				cout << "Enter Resident ID: ";
				cin >> elec.resid;
				cout << "Enter Payment Date (DD-MON-YYYY): ";
				cin >> elec.date;
				cout << "Enter Amount: ";
				cin >> elec.amount;
				cout << "Enter Bank Number: ";
				cin >> elec.banknumber;

				Statement* stmt = conn->createStatement();
				stmt->setSQL("BEGIN spElectricityInsert1(:1, :2, :3, :4, :5, :6); END;");
				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
				stmt->setNumber(2, elec.suiteid);
				stmt->setNumber(3, elec.resid);
				stmt->setString(4, elec.date);
				stmt->setNumber(5, elec.amount);
				stmt->setNumber(6, elec.banknumber);

				stmt->executeUpdate();
				err = stmt->getInt(1);

				if (err == -1) {
					cout << endl;
					cout << "ERROR : Cannot be inserted" << endl;

					cout << endl;
				}
				else {
					cout << endl;
					cout << "--- SUCCESSFULLY INSERTED ---" << endl;
					cout << endl;
				}
				conn->terminateStatement(stmt);
			}
			else if (input == 2) {
				string val;
				string new_data;
				ok = true;
				int err = 0;
				Electricity elec;
				cout << endl << "-- WHAT TO UPDATE --" << endl;
				cout << "1) Update Resident ID" << endl;
				cout << "2) Update Payment Date" << endl;
				cout << "3) Update Amount" << endl;
				cout << "4) Update Bank Number" << endl;
				cout << "Enter the value: ";
				cin >> val;
				cout << "Enter Suite ID: ";
				cin >> elec.suiteid;
				cout << "Enter the new data: ";
				cin >> new_data;
				Statement* stmt = conn->createStatement();
				stmt->setSQL("BEGIN spElectricityUpdate(:1, :2, :3, :4); END;");
				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
				stmt->setString(2, val);
				stmt->setNumber(3, elec.suiteid);
				stmt->setString(4, new_data);
				stmt->executeUpdate();
				err = stmt->getInt(1);

				if (err > 0) {
					cout << endl;
					cout << "--- UPDATED TO: " << new_data << " ---" << endl;
					cout << endl;
				}
				else {
					cout << endl;
					cout << "ERROR - CANNOT BE UPDATED" << endl;
					cout << endl;
				}
				conn->terminateStatement(stmt);
			}
			else if (input == 3) {
				ok = true;
				int err = 0;
				Electricity elec;
				cout << "Enter Suite ID: ";
				cin >> elec.suiteid;

				Statement* stmt = conn->createStatement();
				stmt->setSQL("BEGIN spElectricityDelete(:1, :2); END;");
				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
				stmt->setNumber(2, elec.suiteid);

				stmt->executeUpdate();
				err = stmt->getInt(1);

				if (err == -1) {
					cout << endl;
					cout << "ERROR : Cannot be deleted" << endl;

					cout << endl;
				}
				else {
					cout << endl;
					cout << "--- SUCCESSFULLY DELETED ---" << endl;
					cout << endl;
				}
				conn->terminateStatement(stmt);
			}
			else if (input == 4) {
				ok = true;
				int err = 0;
				Electricity elec;
				cout << "Enter Suite ID: ";
				cin >> elec.suiteid;
				Statement* stmt = conn->createStatement();
				stmt->setSQL("BEGIN spElectricitySelect(:1, :2, :3, :4, :5, :6); END;");
				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
				stmt->setNumber(2, elec.suiteid);
				stmt->registerOutParam(3, Type::OCCIINT, sizeof(elec.resid));
				stmt->registerOutParam(4, Type::OCCISTRING, sizeof(elec.date));
				stmt->registerOutParam(5, Type::OCCIDOUBLE, sizeof(elec.amount));
				stmt->registerOutParam(6, Type::OCCIINT, sizeof(elec.banknumber));

				stmt->executeUpdate();

				err = stmt->getInt(1);
				elec.resid = stmt->getInt(3);
				elec.date = stmt->getString(4);
				elec.amount = stmt->getDouble(5);
				elec.banknumber = stmt->getInt(6);

				if (err > 0) {
					cout << endl;
					cout << "---------- READ ----------" << endl;
					cout << "Suite ID: " << elec.suiteid << endl;
					cout << "Resident ID: " << elec.resid << endl;
					cout << "Payment Date: " << elec.date << endl;
					cout << "Amount: " << elec.amount << endl;
					cout << "Bank Number: " << elec.banknumber << endl;
					cout << "--------------------------" << endl;
					cout << endl;
				}
				else {
					cout << endl;
					cout << "ERROR - DOES NOT EXIST" << endl;
					cout << endl;
				}
				conn->terminateStatement(stmt);
			}
			else if (input == 5) {
				cout << "\nSHUBHDEEP - CREATE\n" << endl;
				ok = true; //do not remove
				int err = 0;

				Residents resi;

				cout << "Enter Resident ID: ";

				cin >> resi.residentid;

				cout << "Enter First Name: ";

				cin >> resi.firstname;

				cout << "Enter Last Name: ";

				cin >> resi.lastname;

				cout << "Enter Suite Number: ";

				cin >> resi.suitenumber;

				cout << "Enter Phone Number: ";

				cin >> resi.phonenumber;

				Statement* stmt = conn->createStatement();

				stmt->setSQL("BEGIN spResidentsInsert(:1, :2, :3, :4, :5, :6); END;");

				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));

				stmt->setNumber(2, resi.residentid);

				stmt->setString(3, resi.firstname);

				stmt->setString(4, resi.lastname);

				stmt->setNumber(5, resi.suitenumber);

				stmt->setString(6, resi.phonenumber);

				stmt->executeUpdate();

				err = stmt->getInt(1);

				if (err == -1) {

					cout << endl;

					cout << "ERROR : Cannot be inserted" << endl;

					cout << endl;

				}

				else {

					cout << endl;

					cout << "--- SUCCESSFULLY INSERTED ---" << endl;

					cout << endl;

				}

				conn->terminateStatement(stmt);

				
			}
			else if (input == 6) {
				cout << "\nSHUBHDEEP - UPDATE\n" << endl;
				ok = true;	//do not remove
				string val;

				string new_data;

				ok = true;

				int err = 0;

				Residents resi;

				cout << endl << "-- WHAT TO UPDATE --" << endl;

				cout << "1) Update First Name" << endl;

				cout << "2) Update Last Name " << endl;

				cout << "3) Update Suite Number" << endl;

				cout << "4) Update Phone Number" << endl;

				cout << "Enter the value: ";

				cin >> val;

				cout << "Enter Resident ID: ";

				cin >> resi.residentid;

				cout << "Enter the new data: ";

				cin >> new_data;

				Statement* stmt = conn->createStatement();

				stmt->setSQL("BEGIN spResidentsUpdate(:1, :2, :3, :4); END;");

				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));

				stmt->setString(2, val);

				stmt->setNumber(3, resi.residentid);

				stmt->setString(4, new_data);

				stmt->executeUpdate();

				err = stmt->getInt(1);

				if (err > 0) {

					cout << endl;

					cout << "--- UPDATED TO: " << new_data << " ---" << endl;

					cout << endl;

				}

				else {

					cout << endl;

					cout << "ERROR - CANNOT BE UPDATED" << endl;

					cout << endl;

				}
			}
			else if (input == 7) {
				cout << "\nSHUBHDEEP - DELETE\n" << endl;
				ok = true;	//do not remove
				ok = true;

				int err = 0;

				Residents resi;

				cout << "Enter Resident ID: ";

				cin >> resi.residentid;

				Statement* stmt = conn->createStatement();

				stmt->setSQL("BEGIN spResidentsDelete(:1, :2); END;");

				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));

				stmt->setNumber(2, resi.residentid);

				stmt->executeUpdate();

				err = stmt->getInt(1);

				if (err == -1) {

					cout << endl;

					cout << "ERROR : Cannot be deleted" << endl;

					cout << endl;

				}

				else {

					cout << endl;

					cout << "--- SUCCESSFULLY DELETED ---" << endl;

					cout << endl;

				}

				conn->terminateStatement(stmt);
			}
			else if (input == 8) {
				cout << "\nSHUBHDEEP - READ\n" << endl;
				ok = true;	//do not remove
				int err = 0;

				Residents resi;

				cout << "Enter Resident ID: ";

				cin >> resi.residentid;

				Statement* stmt = conn->createStatement();

				stmt->setSQL("BEGIN spResidentsSelect(:1, :2, :3, :4, :5, :6); END;");

				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));

				stmt->setNumber(2, resi.residentid);

				stmt->registerOutParam(3, Type::OCCISTRING, sizeof(resi.firstname));

				stmt->registerOutParam(4, Type::OCCISTRING, sizeof(resi.lastname));

				stmt->registerOutParam(5, Type::OCCIINT, sizeof(resi.suitenumber));

				stmt->registerOutParam(6, Type::OCCISTRING, sizeof(resi.phonenumber));

				stmt->executeUpdate();

				err = stmt->getInt(1);

				resi.firstname = stmt->getString(3);

				resi.lastname = stmt->getString(4);

				resi.suitenumber = stmt->getInt(5);

				resi.phonenumber = stmt->getString(6);

				if (err > 0) {

					cout << endl;

					cout << "---------- READ ----------" << endl;

					cout << "Resident ID: " << resi.residentid << endl;

					cout << "First Name: " << resi.firstname << endl;

					cout << "Last Name: " << resi.lastname << endl;

					cout << "Suitenumber: " << resi.suitenumber << endl;

					cout << "Phone Number: " << resi.phonenumber << endl;

					cout << "--------------------------" << endl;

					cout << endl;

				}

				else {

					cout << endl;

					cout << "ERROR - DOES NOT EXIST" << endl;

					cout << endl;

				}

				conn->terminateStatement(stmt);

			}
			else if (input == 9) {
				cout << "\nGAYATRI - CREATE\n" << endl;
				ok = true;	//do not remove
				int err = 0;
				Packages pack;
				cout << "Enter Resident ID: ";
				cin >> pack.residentid;
				cout << "Enter Resident Name: ";
				cin >> pack.residentname;
				cout << "Enter Suite Number: ";
				cin >> pack.suitenumber;
				cout << "Enter Package Details: ";
				cin >> pack.packagedetails;
				cout << "Enter Delivery Provider: ";
				cin >> pack.deliveredby;
				Statement* stmt = conn->createStatement();
				stmt->setSQL("BEGIN spPackagesInsert(:1, :2, :3, :4, :5, :6); END;");
				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
				stmt->setNumber(2, pack.residentid);
				stmt->setString(3, pack.residentname);
				stmt->setNumber(4, pack.suitenumber);
				stmt->setString(5, pack.packagedetails);
				stmt->setString(6, pack.deliveredby);
				stmt->executeUpdate();
				err = stmt->getInt(1);
				if (err == -1) {
					cout << endl;
					cout << "ERROR : Cannot be inserted" << endl;
					cout << endl;
				}
				else {
					cout << endl;
					cout << "--- SUCCESSFULLY INSERTED ---" << endl;
					cout << endl;
				}
				conn->terminateStatement(stmt);
			}
			else if (input == 10) {
				cout << "\nGAYATRI - UPDATE\n" << endl;

				
				string val;

				string new_data;

				ok = true;

				int err = 0;

				Packages pack;

				cout << endl << "-- WHAT TO UPDATE --" << endl;

				cout << "1) Update Resident Name" << endl;
				cout << "2) Update Suite Number" << endl;
				cout << "3) Update Package Details" << endl;
				cout << "4) Update Delivery Provider" << endl;

				cout << "Enter the value: ";
				cin >> val;

				cout << "Enter Resident ID: ";
				cin >> pack.residentid;

				cout << "Enter the new data: ";
				cin >> new_data;

				Statement* stmt = conn->createStatement();

				stmt->setSQL("BEGIN spPackagesUpdate(:1, :2, :3, :4); END;");

				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));

				stmt->setString(2, val);
				stmt->setNumber(3, pack.residentid);
				stmt->setString(4, new_data);
				stmt->executeUpdate();
				err = stmt->getInt(1);

				if (err > 0) {

					cout << endl;
					cout << "--- UPDATED TO: " << new_data << " ---" << endl;
					cout << endl;

				}

				else {

					cout << endl;
					cout << "ERROR - CANNOT BE UPDATED" << endl;
					cout << endl;

				}

			}
			else if (input == 11) {
				cout << "\nGAYATRI - DELETE\n" << endl;
				ok = true;	//do not remove
				int err = 0;
				Packages pack;
				cout << "Enter Resident ID: ";
				cin >> pack.residentid;
				Statement* stmt = conn->createStatement();
				stmt->setSQL("BEGIN spPackagesDelete(:1, :2); END;");
				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));
				stmt->setNumber(2, pack.residentid);
				stmt->executeUpdate();
				err = stmt->getInt(1);
				if (err == -1) {
					cout << endl;
					cout << "ERROR : Cannot be deleted" << endl;
					cout << endl;
				}
				else {
					cout << endl;
					cout << "--- SUCCESSFULLY DELETED ---" << endl;
					cout << endl;
				}
				conn->terminateStatement(stmt);
			}
			else if (input == 12) {
				cout << "\nGAYATRI - READ\n" << endl;
				ok = true;	//do not remove

				int err = 0;
				Packages pack;

				cout << "Enter Resident ID: ";

				cin >> pack.residentid;

				Statement* stmt = conn->createStatement();

				stmt->setSQL("BEGIN spPackagesSelect(:1, :2, :3, :4, :5, :6); END;");

				stmt->registerOutParam(1, Type::OCCIINT, sizeof(err));

				stmt->setNumber(2, pack.residentid);
				stmt->registerOutParam(3, Type::OCCISTRING, sizeof(pack.residentname));
				stmt->registerOutParam(4, Type::OCCIINT, sizeof(pack.suitenumber));
				stmt->registerOutParam(5, Type::OCCISTRING, sizeof(pack.packagedetails));
				stmt->registerOutParam(6, Type::OCCISTRING, sizeof(pack.deliveredby));

				stmt->executeUpdate();

				err = stmt->getInt(1);
				pack.residentname = stmt->getString(3);
				pack.suitenumber = stmt->getInt(4);
				pack.packagedetails = stmt->getString(5);
				pack.deliveredby = stmt->getString(6);

				if (err > 0) {

					cout << endl;
					cout << "---------- READ ----------" << endl;
					cout << "Resident ID: " << pack.residentid << endl;
					cout << "Resident Name: " << pack.residentname << endl;
					cout << "Suitenumber: " << pack.suitenumber << endl;
					cout << "Package details: " << pack.packagedetails << endl;
					cout << "Delivery Provider: " << pack.deliveredby << endl;
					cout << "--------------------------" << endl;
					cout << endl;

				}

				else {

					cout << endl;
					cout << "ERROR - DOES NOT EXIST" << endl;
					cout << endl;

				}

				conn->terminateStatement(stmt);
			}
			else if (input == 0) {
				ok = false; //do not remove
			}
		} while (ok == true);
		cout << endl << "HIGH RAISE CONDO MAINTENANCE EXITED !!" << endl;
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;



}