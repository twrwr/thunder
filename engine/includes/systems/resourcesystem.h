#ifndef RESOURCESYSTEM_H
#define RESOURCESYSTEM_H

#include "system.h"

typedef unordered_map<string, string> StringMap;

class Resource;

class NEXT_LIBRARY_EXPORT ResourceSystem : public ISystem {
public:
    bool init () override;

    const char *name () const override;

    void update (Scene *) override;

    bool isThreadSafe() const override;

    void setResource(Object *object, const string &uuid);

    Object *loadResource(const string &path);

    void unloadResource(const string &path);

    string reference(Object *object);

    StringMap &indices() const;
};

#endif // RESOURCESYSTEM_H
