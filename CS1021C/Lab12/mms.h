#ifndef __MMS_H
#define __MMS_H

#include "adoptable.h"
#include "date.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class MMS {

public:
    MMS() { adoptables = std::vector<std::unique_ptr<Adoptable>>(); }
    /*
    * addAdoptable()
    *
    * pushes back the next thing in the class adotable to the private adoptables
    *
    * input: std::unique_ptr<Adoptable>&& a
    * output: adoptables.push_back()
    *
    */
    void addAdoptable(std::unique_ptr<Adoptable>&& a) {
        adoptables.push_back(std::move(a));
    }
    /*
    * printInventory()
    *
    * it will print everything in adoptables
    *
    * input: none
    * output: adoptables
    */

    void printInventory() const {
        for (auto& adoptable : adoptables) {
            adoptable->print();
        }
    }

    int inventorySize();

    int inventorySizeByShots(bool has_shots = true) const;

    int inventorySizeByType(AdoptableType type = ALL) const;

    int inventorySizeByRestrictions(bool has_restrictions = true) const;

    std::vector<std::string> animalsInInventory() const;

private:
    std::vector<std::unique_ptr<Adoptable>> adoptables;
};

#endif