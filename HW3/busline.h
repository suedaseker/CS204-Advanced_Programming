#ifndef _BUSLINE_H
#define _BUSLINE_H

using namespace std;

struct busStop
{
	string busStopName;
	busStop *left;
	busStop *right;
	
	//constructor
	busStop::busStop(string bsn, busStop *L = NULL, busStop *R= NULL)
			:busStopName(bsn), left(L), right(R) {}
};

struct busLine 
{
	string busLineName;
	busLine *next;
	busStop *busStops;

	//constructor
	busLine::busLine(string bln, busLine *n = NULL, busStop *bss = NULL)
			:busLineName(bln), next(n), busStops(bss) {}
};

//a struct that stores bus line and its stop name
struct LineStop
{
	string busLineName;
	string busStopName;

	//constructor
	LineStop::LineStop(string line, string stop): busLineName(line), busStopName(stop){};
};

class LinkedList
{
private:
	busLine *head;

public:
	LinkedList();

	void BusLineList(string &line_name, string &stop_name, const int &endorbeginning);
	void BusStopList(string &line_name, string &stop_name);

	bool consistencyCheck();
	bool IsInVector(vector<string> &bus_stops, string &stop_name);
	bool IsInLineList(string &line_name);
	bool IsInLine(string &line_name, string &stop_name);
	bool IsInTable(string &stop_name);
	void printBusLines(string &line_name);
	void deleteline(string &line_name);

	void addBusLine(); 
	void addBusStop();
	void deleteBusLine();
	void deleteBusStop();
	void pathfinder();
	void pathfinder2();
	void pathFinder(string start, string stop, vector<LineStop> from, int& );

	void printMainMenu();
	void processMainMenu() ;
};

#endif