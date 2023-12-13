#ifndef MenuItem_h
#define MenuItem_h

#include <Arduino.h>

#define FlashString __FlashStringHelper

//  Abstract class

class MenuItem {
    protected:
        MenuItem* parent;

        const char* text;
        bool enabled, edited;
    public:
        MenuItem(MenuItem* parent, const FlashString* text) : parent(parent), enabled(true), edited(false) { setText(text); }

        virtual MenuItem* getParent() { return parent; }
        virtual void setParent(MenuItem* parent) { this->parent = parent; }

        virtual const char* getText() { return text; }
        virtual void  setText(const FlashString* text) { this->text = reinterpret_cast<PGM_P>(text); }

        virtual const char* getSecondaryText() { return NULL; }

        virtual char getTypeId() = 0;

        virtual bool isEnabled() { return this->enabled; }
        virtual void setState(bool enabled) { this->enabled = enabled; }

        virtual bool isEdited() { return this->edited; }
        virtual void setEditingState(bool edited) { this->edited = edited; }

        // Called when the parent menu select the item

        /* Ritorna un booleano
           Se vero:  l'oggetto vorrà prendere il controllo
           Se false: l'oggetto ritornerà subito il controllo al padre.
        */
        virtual bool activate() = 0;

        // Triggered when the current action is cancelled. (Back button pressed)
        // TODO: Determine what this function can return
        virtual void deactivate() = 0;

        // This events are triggerd only if the item is active.
        // ------

        // Called when event "next" is triggered
        // Usually this event is triggered when a down or right key is pressed
        virtual void doIncr() = 0;
        virtual void doIncrFast() = 0;

        // Called when event "prev" is triggered
        // Usually this event is triggered when up or left key is pressed
        virtual void doDecr() = 0;
        virtual void doDecrFast() = 0;

        // Called when event "action" is triggered
        // Usually this event is triggered when center or ok key is pressed

        // Ritorna un puntatore ad un MenuItem che verrà attivato.
        // Se ritorna this o NULL, l'oggetto stesso manterrà il controllo.
        virtual MenuItem* action() = 0;

        virtual bool esc() { return true; }

        virtual ~MenuItem() {}
};

#endif
