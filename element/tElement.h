#ifndef TELEMENT_H_
#define TELEMENT_H_

#include <QString>
#include <QMutex>
#include <QMutexLocker>

#include "classes/tList.h"
#include "classes/tVector.h"
#include "classes/tRGB.h"
#include "classes/jrTypes.h"

#include "element/iElement.h"

#include <map>

extern QMutex jrMutex;

#define setElementLocked QMutexLocker locker(&jrMutex);


class tElement
{
    /**
 * \brief tElement is the basic class for all elements within this parametric geometry model.
 *
 * These elements have the possibility to depend on other elements, so if one of its supports
 * changes, the element will adapt to this new situation. Hence an element has to know about it dependencies.
 * If one of its properties changes it becomes invalid and it will call the invalidate() function of
 * the dependent elements. This will also invalidate them, and so on. If one of the element properties
 * is accessed it first has to call the update() function which will set the isValid variable to true
 * and will call the refresh() function subsequently. As the actions executed during refresh() depend on
 * the type of the element, the refresh() function has to be implemented in any function which inherits
 * tElement.
 *
 * tElement has its own memory management. An element will delete itself, if it does not have any dependents
 * longer. As this behavior would result in difficult states, where the user does not know, whether an element
 * is still available in memory, each element can have one or more owners. So, if both, the owners are removed and also no
 * dependents are available, the element will delete itself. Hence an element should never be destroyed with the
 * delete command.
 *
 * Each element has a corresponding interface-class called iElementClassName instead of tElementClassName, which
 * allows a standardised access to its properties, e.g. name, color, ...
 *
 * As tElement can be used in mutithreaded environments, a Mutex might be needed. If the element should be locked
 * during the access of a function, the macro setElementLocked can be used. The QMutex *jrMutex is a global variable
 * typically defined in the main function.
 */
    /* -- tElement ------------------------------------------------------
 *
 * Die Basisklasse fuer alle Elemente der Geometrieklasse.
 *
 * Speichert die Abhaengigkeit zwischen Elementen, und veranlasst die
 * Aktualisierung der abhaengigen Elemente, wenn sich eine Eigenschaft
 * Elements aendert.
 *
 * Abgeleitete Elemente muessen die Funktion refresh implementieren.
 * "refresh" veranlasst, dass sich das Element aktualisiert. (Bsp. sollen die
 * Koeffizienten eines Splines in der Funktion berechnet werden.)
 *
 * Ein von tElement abgeleitetes Objekt wird mit new... instanziiert.
 * Es loescht sich selbst, wenn es keine abhaengigen Elemente mehr gibt,
 * dass heisst, wenn mittels "removeDependent" das letzte abhaengige Element
 * aus der Liste "dependent" entfernt wird. Wird dem Konstruktor ein
 * tElement-Zeiger uebergeben, wird dieser als erster der Liste "dependent"
 * hinzugefuegt.
 * Elemente sollten nie mit delete geloescht werden.
 *
 *
 *
 * -----------------------------------------------------------------*/
private:
    virtual void refresh(void) = 0;
    QList<tElement*> fdependent;
    QList<void*> owner;

protected:
    bool isValid; // gibt an, ob alle Eigenschaften noch aktuell/ konsistent sind.
    iElement *iface;
    tList<tElement*> blockInvalidateList; //Alle Elemente in dieser Liste verhindern, dass invalidate(tElement) die Elemente aus der Liste fdependent aufruft.


public:
    tElement(void* theOwner);
    virtual ~tElement();

    void lockElement(void){jrMutex.lock();}
    void unlockElement(void){jrMutex.unlock();}

    virtual void invalidate(tElement *sender);
    virtual void repaintElement(tElement *sender);
    void update(void);

    bool addDependent(tElement *element);
    void removeDependent(tElement *element);

    tElement* dependent(int index);
    //void addDirectDependents(tList<tElement*> *list);
    //void addAllDependents(tList<tElement*> *list);
    tList<tElement*> dependents(bool recursive = false);
    bool isSupportOf(tElement* element);

    virtual void addOwner(void *theOwner);
    virtual bool releaseOwner (void *theOwner);
    bool hasOwner(void* test) {setElementLocked return owner.contains(test);}

    virtual iElement* intrface(void);
    bool hasInterface(void){if (iface!=NULL) return true; else return false;}

    virtual tVector xMin(void);
    virtual tVector xMax(void);

};
#endif /*TELEMENT_H_*/
