#include <iostream>
#include <string>
#include <Windows.h>
class Colleague;


class Mediator {
public:
    virtual void sendMessage(const std::string& message, Colleague* colleague) const = 0;
    virtual ~Mediator() = default;
};


class Colleague {
protected:
    Mediator* mediator;

public:
    Colleague(Mediator* m) : mediator(m) {}

    virtual void send(const std::string& message) const {
        mediator->sendMessage(message, const_cast<Colleague*>(this));
    }

    virtual void receiveMessage(const std::string& message) const = 0;
};


class ConcreteMediator : public Mediator {
private:
    Colleague* colleague1;
    Colleague* colleague2;

public:
    void setColleague1(Colleague* c) {
        colleague1 = c;
    }

    void setColleague2(Colleague* c) {
        colleague2 = c;
    }

    void sendMessage(const std::string& message, Colleague* colleague) const override {
        if (colleague == colleague1) {
            colleague2->receiveMessage(message);
        }
        else if (colleague == colleague2) {
            colleague1->receiveMessage(message);
        }
    }
};


class ConcreteColleague : public Colleague {
public:
    using Colleague::Colleague;

    void receiveMessage(const std::string& message) const override {
        std::cout << "Колега отримав повідомлення: " << message << std::endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ConcreteMediator mediator;
    ConcreteColleague colleague1(&mediator);
    ConcreteColleague colleague2(&mediator);

    mediator.setColleague1(&colleague1);
    mediator.setColleague2(&colleague2);

    colleague1.send("Привіт, колего 2!");
    colleague2.send("Привіт, колего 1!");

    return 0;
}