// Created by: Leo Martinez III, Jalen Williams, Lane


/**
 * Comments using this: /* are direct quotes from the assignment.
 * Comments using these: // are quotes from websites or descriptive.
 * Don't forget to backup whatever changes you make.
 */

 // If you follow along with these comments, I'm going to show how we could add  <<<<<<<<<<
 // another co2 source to one of our three classes.
 // If you'd like to add an attribute to one of the classes right now, go to the
 // next comment marked with <<<<<<<<<< on the right-hand side (like there was on
 // line 7, you might need to widen the text view a lil bit). It's in main().

 // There are potential divide-by-zero errors on lines 130 and 213. These should
 // be handled by exceptions thrown by the appropriate constructor.

 // To add more things to this, we could think about "what attributes of our
 // three classes are equivalent somehow to CO2?" Many things that our classes
 // might consume or be composed of are related to the release of a certain
 // amount of CO2. For example, the fuel burned in the Car actually turns into a
 // certain amount of CO2 during combustion. As another example, the production
 // of electricity is merely _related_ to the release of a certain amount of CO2,
 // as this amount is something like a national average. Electric generation may
 // not cause the release of CO2 directly in every case.
 //      Maybe we could somehow separate the attributes according to when the CO2
 // cost comes into play. We might be able to separate all attributes into the
 // following categories: costs of construction, cost of maintenance/use, and
 // cost of disposal. This would add complexity.
 //      Another thing we could do is report results in units CO2e, which means
 // CO2-equivalent. This would allow us to add a wider variety of attributes to
 // our classes. Refrigerants are more polluting than CO2, and many (most?) cars
 // contain a certain amount of refrigerant that will probably at some point
 // leak out. There are CO2e numbers available for things like refrigerants,
 // methane (maybe our building is full of cows), nitrous oxide (maybe the car is
 // fast), and other stuff. This site
 // https://greencleanguide.com/how-to-calculate-carbon-dioxide-equivalent-emissions-from-different-ghg-sources/
 // gives some examples of some CO2e values.
 //      See:
 // https://www.scu.edu/media/ethics-center/environmental-ethics/carbon-footprint/Math_and_Methodologies_Behind_This_Calculator.pdf
 // for some interesting examples mostly involving amounts of CO2 released with
 // respect to time.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// This struct represents the attributes of a source of CO2. Each of the three
// derived classes below have vectors of Co2Sources in addition to their own
// unique attributes and behaviors. The name of each source of CO2 is mapped to
// an appropriate Co2Source object in the initializeConversionMap function.
struct Co2Source {
    // name - the name of the co2 source
    // quantity - the amount of the substance
    // units - the units that the quantity is in
    // co2Factor - how many metric tons of co2 are in 1 unit of the substance
    Co2Source(string name, string units, double co2Factor, double quantity = 0)
        : name(name), units(units), co2Factor(co2Factor), quantity(quantity) {}
    string name, units;
    double co2Factor, quantity;
};

/**
 * Write an abstract class CarbonFootprint with only a pure virtual
 * getCarbonFootprint method.
 */
class CarbonFootprint {
public:
    virtual double getCarbonFootprint() = 0;

};

/**
 * Create three small classes unrelated by inheritance—classes Building, Car and
 * Bicycle.Give each class some unique appropriate attributes and behaviors that
 * it does not have in common with other classes. Have each of your classes
 * inherit from that abstract class and implement the getCarbonFootprint method
 * to calculate an appropriate carbon footprint for that class (check out a few
 * websites that explain how to calculate carbon footprints).
 */

class Building : CarbonFootprint {
    // from "buildings.com" lol:
    // https://www.buildings.com/articles/30925/how-calculate-your-carbon-footprint
    // The bulk of a building’s footprint is energy use, including electricity,
    // natural gas, and other sources tied to fossil fuel. Review your utility
    // bills and conduct some basic calculations to reveal a large portion of
    // these impacts.

public:
    Building(string name) : name(name) {}

    double getCarbonFootprint() {
        double sum = 0;
        for (auto& source : co2Sources) sum += source.co2Factor * source.quantity;
        return sum;
    }

    string print() {
        ostringstream s;
        s << '+' << string(48, '=') << '+' << endl
            << "| Building - " << right << setw(35) << name << " |" << endl
            << '+' << string(48, '=') << '+' << endl
            << "| CO2 sources:" << right << setw(36) << "|" << endl;
        for (auto& source : co2Sources) {
            s << left << setw(6) << '|' << left << setw(13) << source.name + ", ";
            ostringstream quantity;
            quantity << setprecision(3) << source.quantity << ' ' << source.units;
            s << right << setw(15) << quantity.str() << " = " << left << setw(4)
                << setprecision(3) << source.quantity * source.co2Factor << " mt CO2 |"
                << endl;
            // s << "| " << source.name << ", " << setprecision(3) << source.quantity << ' '
            //   << source.units << " = " << setprecision(3) << source.quantity * source.co2Factor
            //   << " mt CO2" << endl;
        }
        s << '+' << string(48, '=') << '+' << endl;
        return s.str();
    }

    Building* addSource(Co2Source source, double quantity) {
        source.quantity = quantity;
        co2Sources.push_back(source);
        return this;
    }

private:
    vector<Co2Source> co2Sources;
    string name;
};

class Car : CarbonFootprint {
public:
    Car(string typeOfCar, double mpg, Co2Source fuel, double mileage)
        : mpg(mpg), typeOfCar(typeOfCar), fuel(fuel), mileage(mileage) {}

    double getCarbonFootprint() {
        double sum = fuel.co2Factor * mileage / mpg;
        for (auto& source : secondaryCo2Sources)
            sum += source.co2Factor * source.quantity;
        return sum;
    }

    string print() {
        ostringstream s;
        s << '+' << string(42, '=') << '+' << endl
            << "| Car - " << right << setw(34) << typeOfCar << " |" << endl
            << '|' << right << setw(24) << "fuel: " << fuel.name << ", mpg: " << mpg
            << " |" << endl
            << '+' << string(42, '-') << '+' << endl
            << "| CO2 sources:" << right << setw(30) << "|" << endl
            << left << setw(6) << '|' << "mileage, " << right << setw(7)
            << setprecision(3) << mileage << left << setw(9) << " miles = "
            << fuel.co2Factor * mileage / mpg << " mt CO2 |" << endl;
        for (auto& source : secondaryCo2Sources) {
            s << left << setw(6) << '|' << left << setw(9) << source.name + ", "
                << left << setw(11);
            ostringstream quantity;
            quantity << source.quantity << ' ' << source.units;
            s << quantity.str() << " = " << left << setw(5) << setprecision(3)
                << source.quantity * source.co2Factor << "mt CO2 |" << endl;
        }
        s << '+' << string(42, '=') << '+' << endl;
        return s.str();
    }

    Car* addSecondaryCo2Source(Co2Source source, double quantity) {
        source.quantity = quantity;
        secondaryCo2Sources.push_back(source);
        return this;
    }

private:
    // this is "vehicle miles traveled", this is an annual average
    // see https://www.epa.gov/energy/greenhouse-gases-equivalencies-calculator-calculations-and-references
    static const int vmt = 11484;
    string typeOfCar;
    Co2Source fuel;
    vector<Co2Source> secondaryCo2Sources;
    double mpg, mileage;
};

class Bicycle : CarbonFootprint {
public:
    // material - what the bike is made of.
    // time - how many hours was the bike ridden?
    Bicycle(Co2Source material, double time, double riderWeight)
        : material(material), time(time), riderWeight(riderWeight) {
        if (material.name == "electric")
            co2Sources.push_back(Co2Source("food", "calories",
                0.00000144, time * riderWeight));
        else
            co2Sources.push_back(Co2Source("food", "calories",
                0.00000144 * 5.3, time * riderWeight));
    }

    double getCarbonFootprint() {
        double sum = material.co2Factor;
        for (auto& source : co2Sources) sum += source.co2Factor * source.quantity;
        return sum;
    }

    string print() {
        ostringstream s;
        s << '+' << string(53, '=') << '+' << endl
            << "| Bicycle - " << right << setw(41) << material.name << " |" << endl
            << '|' << right << setw(26) << "rider weight: " << riderWeight
            << "kg, riding time: " << time << " hrs |" << endl
            << '+' << string(53, '-') << '+' << endl
            << "| CO2 sources:" << right << setw(41) << "|" << endl
            << left << setw(6)
            << '|' << "bike construction" << left << setw(13) << "" << " = "
            << material.co2Factor << right << setw(12)
            << "mt CO2 |" << endl;
        for (auto& source : co2Sources) {
            s << left << setw(6) << '|' << left << setw(14) << source.name + ", "
                << left << setw(16);
            ostringstream quantity;
            quantity << setprecision(3) << (source.name == "human breath"
                ? source.quantity / riderWeight : source.quantity) << ' '
                << source.units;
            s << quantity.str() << " = " << setprecision(3) << left << setw(8)
                << source.quantity * source.co2Factor << "mt CO2 |" << endl;
        }
        s << '+' << string(53, '=') << '+' << endl;
        return s.str();
    }

    Bicycle* addSource(Co2Source source, double quantity) {
        if (source.name == "human breath") source.quantity = quantity * riderWeight;
        else source.quantity = quantity;
        co2Sources.push_back(source);
        return this;
    }
private:
    Co2Source material;
    vector<Co2Source> co2Sources;
    double time, riderWeight;
};

int main() {
    // see https://mobilitylabel.com/fietsfeiten-TNO.pdf (use google translate)
    // for bike info
    Co2Source bikeCarbonFiber("carbon fiber", "", 0.067);
    Co2Source bikeStandard("standard commuter bike (mostly aluminum)", "", 0.097);
    Co2Source bikeElectric("electric", "", 0.134);
    Co2Source bikeAluminum("all-aluminum", "", 0.25);
    // see http://www.co2list.org/files/carbon.htm
    Co2Source tires("tire rubber", "kg", 0.0044);
    // see the epa link for these
    Co2Source natGas("natural gas", "therms", 0.005307);
    Co2Source electricity("electricity", "kWh", 0.000707);
    Co2Source gasoline("gasoline", "gallons", 0.00889);
    Co2Source diesel("diesel", "gallons", 0.01018);
    // see https://www.quora.com/What-is-the-mass-of-the-carbon-dioxide-exhaled-in-a-breath
    // note: for breaths, multiply conversion factor by a person's weight in kg
    Co2Source exhaledBreath("human breath", "breaths", 0.00000000051576);
    // from https://www.autozone.com/diy/motor-oil/how-to-recycle-motor-oil
    // "2.5 quarts of motor oil requires 42 gallons of crude oil to produce"
    // from epa.gov "0.43 metric tons CO2/bbl crude oil"
    // -> 0.22933 metric tons CO2/quart motor oil.
    Co2Source unrecycledMotorOil("motor oil", "quarts", 0.22933);

    // Let's say we've decided to add copy paper as a yearly source of CO2 to our <<<<<<<<<<
    // Building class. First, we need to figure out how the copy paper is measured
    // and how much CO2 one unit of copy paper is responsible for.
    //    Online, I found that to produce 1 ton of copy paper requires 11134 kWh,
    // which (using the electricity factor above 11134 * 0.000707 = 7.871738)
    // means that the production of 1 ton of copy paper generates 7.871738 metric
    // tons of CO2. An average ream of copy paper weighs 20lb, so there are 100
    // reams in each ton of copy paper, so the production of 1 ream of copy paper
    // generates 0.07871738 metric tons of CO2.
    //    Let's define a 'copyPaper' Co2Source containing that info:
    Co2Source copyPaper("copy paper", "reams", 0.07871738);
    // Now go to the next <<<<<<<<<< (it's just a few lines down.)

    /* Write an application that creates objects of each of the three classes, */

    // We're ready to add copy paper as a source of CO2 to the Building object.   <<<<<<<<<<
    // This is what the Building instantiation used to look like:
    // Building* A = (new Building())
    //               ->addSource(natGas, 12345);
    // And this is what it looks like when we add the paper CO2 source:
    Building A = Building("Empire State");
    A.addSource(natGas, 12345)->addSource(copyPaper, 300)//;
    // See how we just added the line "->addSource(copyPaper, 300)" and moved the
    // semicolon down? This line we added means "this building uses 300 reams of
    // copy paper". This will be reflected in the total carbon footprint of this
    // Building object, and some information about this copy paper carbon source
    // will be printed. The implementation of print() is not the same in every
    // class, tho.
    //      Also, in the Car class it's not called 'addSource', it's
    // 'addSecondaryCo2Source', since the car's fuel consumption is likely to be
    // the primary source of co2. This wouldn't be true for electric cars, so
    // maybe we should change this.
    //      If you've gotten this far I'd encourage you to try to add a new
    // attribute to one of these classes, and see if what you add is reflected in
    // the output. Maybe this building consumes electricity... maybe 5 MW. If you
    // take the semicolon off the last line of code and uncomment the following
    // line, we'll have a building that uses 5 MW of electricity.
        ->addSource(electricity, 5000);
    // Note that we used the already-defined 'electricity' Co2Source here, since
    // we already have the conversion info for electricity <-> co2.

    Car B = Car("Lamborghini Huracan Performante", 12, gasoline, 8000);
    B.addSecondaryCo2Source(unrecycledMotorOil, 7.93);
    Bicycle C = Bicycle(bikeAluminum, 320, 75);
    C.addSource(tires, 3.8)
        // 75 kg person, 50,000 breaths
        ->addSource(exhaledBreath, 50000);

    /* places pointers to those objects in a vector of CarbonFootprint pointers,*/
    vector<CarbonFootprint*> footprints;
    footprints.push_back((CarbonFootprint*)&A);
    footprints.push_back((CarbonFootprint*)&B);
    footprints.push_back((CarbonFootprint*)&C);

    vector<string> carbonTotals;

    /**
     * then iterates through the vector, polymorphically invoking each object’s
     * getCarbonFootprint method. For each object, print some identifying
     * information and the object’s carbon footprint.
     */
    for (auto& footprint : footprints)
        carbonTotals.push_back("total carbon footprint: "
            + to_string(footprint->getCarbonFootprint())
            + " mt CO2.");

    vector<string>::iterator i = carbonTotals.begin();
    cout << A.print();
    cout << *i << endl << endl;

    cout << B.print();
    i++;
    cout << *i << endl << endl;

    cout << C.print();
    i++;
    cout << *i << endl << endl;
}
