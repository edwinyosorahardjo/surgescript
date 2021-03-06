//
// dictionary.ss
// How to use the Dictionary in SurgeScript
// Copyright 2017-2018 Alexandre Martins <alemartf(at)gmail(dot)com>
//

object "Application"
{
    // a Dictionary is a set of (key, value) pairs
    weight = {
        "Surge": 35,
        "Neon": 20,
        "Charge": 37.5,
        "Gimacian": 70
    };
    
    // main state
    state "main"
    {
        // change some weights ("weight" as in everyday use, that is)
        weight["Neon"] = 25;
        weight["Charge"] += 3;

        // print the weights
        Console.print("Surge weighs " + weight["Surge"] + " kg.");
        Console.print("Neon weighs " + weight["Neon"] + " kg.");
        Console.print("Charge weighs " + weight["Charge"] + " kg.");
        Console.print("Gimacian weighs " + weight["Gimacian"] + " kg.");

        // sum up
        totalWeight = computeTotalWeight();
        Console.print("Together, they weigh a total of " + totalWeight + " kg.");

        // done!
        Application.exit();
    }

    // this function will add all weights stored in the Dictionary.
    fun computeTotalWeight()
    {
        sum = 0;

        foreach(entry in weight)
            sum += entry.value;

        return sum;
    }
}