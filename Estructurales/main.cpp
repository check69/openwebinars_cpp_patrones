#include "Composite.hpp"
#include "decorator.hpp"

int main()
{
    Composite composite{};

    composite.add(std::shared_ptr<Action>(new ActionPrint()));
    composite.add(std::shared_ptr<Action>(new ActionPrint()));
    composite.add(std::shared_ptr<Action>(new ActionPrint()));
    composite.add(std::shared_ptr<Action>(new ActionPrint()));
    composite.add(std::shared_ptr<Action>(new ActionPrint()));

    composite.execute();

    ActionPrint action;

    action.execute();

    getchar();

    std::shared_ptr<Basic> basic(new BarraDecorator(
        std::shared_ptr<Basic>(new BasicString("hola estoy dentro del basic string"))));

    basic->pintar();
    getchar();
}