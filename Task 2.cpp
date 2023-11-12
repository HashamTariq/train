#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Constants
const int TOTAL_JOURNEYS = 8; // Total number of journeys
const int UP_JOURNEYS = 4;    // Number of journeys going up
const int MAX_PASSENGERS_PER_JOURNEY = 480; // Maximum number of passengers per journey
const double UP_COST = 25.0;
const double DOWN_COST = 25.0;
const int GROUP_DISCOUNT_THRESHOLD = 10;

// Structure to represent a train journey
struct TrainJourney
{
    int totalPassengers;
    double totalRevenue;
};

// Function to initialize the screen display and data for the start of the day
void initializeDay(vector<TrainJourney> &journeys)
{
    for (int i = 0; i < TOTAL_JOURNEYS; ++i)
    {
        journeys.push_back({0, 0.0});
    }
}

// Function to display the current screen display
void displayScreen(const vector<TrainJourney> &journeys)
{
    cout << "Electric Mountain Railway Schedule" << endl;
    cout << "---------------------------------" << endl;

    for (int i = 0; i < TOTAL_JOURNEYS; ++i)
    {
        cout << "Journey " << (i + 1) << " - Total Passengers: " << journeys[i].totalPassengers
             << " | Total Revenue: $" << journeys[i].totalRevenue << endl;
    }

    cout << "---------------------------------" << endl;
}

// Function to purchase tickets
void purchaseTickets(vector<TrainJourney> &journeys)
{
    int journeyUp, journeyDown, numPassengers;

    cout << "\nEnter details for ticket purchase:" << endl;
    J: ;
    cout << "Enter journey up (1-" << UP_JOURNEYS << "): ";
    cin >> journeyUp;
    if (journeyUp < 1 || journeyUp > UP_JOURNEYS)
    {
    	cout<<"incorrect enter again"<<endl;
    	goto J;
	}
	k: ;
    cout << "Enter journey down (" << (UP_JOURNEYS + 1) << "-" << TOTAL_JOURNEYS << "): ";
    cin >> journeyDown;
    if (journeyDown <= UP_JOURNEYS || journeyDown > TOTAL_JOURNEYS)
    {
    	cout<<"incorrect enter again"<<endl;
    	goto k;
	}
	L: ;
    cout << "Enter number of passengers: ";
    cin >> numPassengers;
 if (numPassengers <= 0 || numPassengers > MAX_PASSENGERS_PER_JOURNEY)
    {
    	cout<<"incorrect enter again"<<endl;
    	goto L;
	}
    // Validate input
//    if (journeyUp < 1 || journeyUp > UP_JOURNEYS || journeyDown <= UP_JOURNEYS || journeyDown > TOTAL_JOURNEYS || numPassengers <= 0 || numPassengers > MAX_PASSENGERS_PER_JOURNEY)
//    {
//        cout << "Invalid input. Please try again." << endl;
//        return;
//    }

    // Check if total passenger limit is not exceeded
    if (journeys[journeyUp - 1].totalPassengers + numPassengers <= MAX_PASSENGERS_PER_JOURNEY && journeys[journeyDown - 1].totalPassengers + numPassengers <= MAX_PASSENGERS_PER_JOURNEY)
    {
        // Calculate total cost
        double totalCost = numPassengers * UP_COST + numPassengers * DOWN_COST;

        // Apply group discount
        int freeTickets = numPassengers / GROUP_DISCOUNT_THRESHOLD;
        totalCost -= freeTickets * DOWN_COST + freeTickets * UP_COST;

        // Update journey data
        journeys[journeyUp - 1].totalPassengers += numPassengers;
        journeys[journeyUp - 1].totalRevenue += (numPassengers - freeTickets)* UP_COST;

        journeys[journeyDown - 1].totalPassengers += numPassengers;
        journeys[journeyDown - 1].totalRevenue += (numPassengers - freeTickets) * DOWN_COST;

        cout << "\nTickets purchased successfully!" << endl;
        cout << "Total cost: $" << totalCost << endl;
    }
    else
    {
        cout << "\nTotal passenger limit exceeded for the selected journey. Please try again later." << endl;
    }
}

// Function to display the end-of-day summary
void endOfDaySummary(const vector<TrainJourney> &journeys)
{
    cout << "\nEnd of Day Summary" << endl;
    cout << "-------------------" << endl;

    int totalPassengers = 0;
    double totalRevenue = 0.0;
    int maxPassengers = 0;
    int maxJourney = 0;

    for (int i = 0; i < TOTAL_JOURNEYS; ++i)
    {
        cout << "Journey " << (i + 1) << " - Total Passengers: " << journeys[i].totalPassengers
             << " | Total Revenue: $" << journeys[i].totalRevenue << endl;

        totalPassengers += journeys[i].totalPassengers;
        totalRevenue += journeys[i].totalRevenue;

        if (journeys[i].totalPassengers > maxPassengers)
        {
            maxPassengers = journeys[i].totalPassengers;
            maxJourney = i + 1;
        }
    }

    cout << "\nTotal Passengers for the Day: " << totalPassengers << endl;
    cout << "Total Revenue for the Day: $" << totalRevenue << endl;
    cout << "Journey with the Most Passengers: Journey " << maxJourney << " with " << maxPassengers << " passengers." << endl;
}

int main()
{
    vector<TrainJourney> journeys;

    // Task 1 - Start of the day
    initializeDay(journeys);

    // Booking loop
    char endOfDayChoice;
    do
    {
        // Task 2 - Purchasing tickets
        displayScreen(journeys);
        purchaseTickets(journeys);

        cout << "\nDo you want to continue booking? (Y/N): ";
        cin >> endOfDayChoice;

    } while (toupper(endOfDayChoice) == 'Y');

    // Task 3 - End of the day
    endOfDaySummary(journeys);

    return 0;
}

