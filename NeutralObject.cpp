#include "NeutralObject.h"
#include "Base.h" 

void ResourceStrategy::apply(Unit& unit) {
    cout << "(Strategy) Ресурсы, собранные юнитом " << unit.getId() << endl;
    if (base) {
        base->addResources(50);
        cout << "(Strategy) Ресурсы базы увеличены на 50. Теперь: " << base->getResources() << endl;
    }
}