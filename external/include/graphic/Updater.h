#pragma once

class Updater
{
    public:
        virtual void Update() = 0;
    protected:
        virtual ~Updater() {}
};