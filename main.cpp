#include <stdio.h>
#include <iostream>

#include <zmqpp/zmqpp.hpp>

using namespace std;

double x_prev = 1.0;
double y_prev = -1.0;
bool is_running = true;

string parseInputString(string in)
{
	string out;
	try
	{
		// commas may delimit new commands 
		size_t comma_idx = in.find(',');
		string command = in.substr(0, comma_idx);
        if (command == "s") {
			is_running = false;
			out = "shutdown,";
		} else if (command == "xy") {
			out = "x" + to_string(x_prev) + "y" + to_string(y_prev) + ",";
		} else {
			cout << "Warning: Command (" << command << ") could not be parsed..." << endl;
			out = "-,";
		}

		if (comma_idx != string::npos && comma_idx < in.length() - 1)
			return out + parseInputString(in.substr(comma_idx+1));
	}
	catch(const std::exception& e)
	{
		std::cerr << "Parsing Error: " << e.what() << '\n';
		return "error,";
	}
	return out;
}

int main(int argc, char* argv[])
{
	const string endpoint = "tcp://*:5555";
	// initialize the 0MQ context
	zmqpp::context context;
	// generate a pull socket
	zmqpp::socket_type type = zmqpp::socket_type::reply;
	zmqpp::socket socket (context, type);
	// bind to the socket
	socket.bind(endpoint);
	cout << "Listening on port: " << endpoint << endl;

	int timeout = 20; // 20ms timeout
	socket.set(zmqpp::socket_option::receive_timeout, timeout);

	while (is_running) {
		// receive the message
		zmqpp::message message;

		if (socket.receive(message))
		{
			// Parse message
			string text;
			message >> text;

			cout << "Dummy ZMQ Socket Received: " << text << endl;
			
			string ret = parseInputString(text);
			socket.send(ret);
		}
		
	}
	return 0;
}