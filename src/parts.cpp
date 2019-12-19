#include <iostream>
using namespace std;
#include "parts.h"

NameContainer partContainer;

void Part::describe(void)
{
    cout << "Part " << name << " subparts are:" << endl;

    if (subparts.empty())
    {
        cout << "  It has no subparts." << endl;
    }
    
    for (pair<Part*, int> subpart : subparts)
    {
        cout << "  " << subpart.second << ' ' << subpart.first->name << endl;
    }
}

int Part::count_howmany(Part const *p)
{
    if (name == p->name)
    {
        return 1;
    }

    int sum = 0;
    for (pair<Part* const, int> subpart : subparts)
    {
        if (subpart.first->name == p->name)
        {
            return subpart.second;
        }

        if (!subpart.first->subparts.empty())
        {
            sum += subpart.first->count_howmany(p) * subpart.second;
        }
    }

    return sum;
}

Part *NameContainer::lookup(string const &name)
{
    if (name_map.find(name) != name_map.end())
    {
        return name_map[name];
    }
    else
    {
        Part* part = new Part(name);
        name_map[name] = part;

        return part;
    }
}

NameContainer::~NameContainer(void)
{
    for (pair<string, Part*> parts : name_map)
    {
        delete parts.second;
    }
}

void add_part(string const &x, int q, string const &y)
{
    Part* xPart = partContainer.lookup(x);
    Part* yPart = partContainer.lookup(y);
    xPart->subparts[yPart] = q;
}
