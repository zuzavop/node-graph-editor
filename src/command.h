#ifndef COMMAND_H
#define COMMAND_H

class Command {
    public:
	virtual void execute() = 0;
};

class QuitCommand : public Command {
public:
    QuitCommand(bool& running) : running_(running) {}
    void execute() override {
        running_ = false;
    }
private:
    bool& running_;
};

class SaveCommand : public Command {
public:
    SaveCommand(bool& running) : running_(running) {}
    void execute() override {
        running_ = false;
    }
private:
    bool& running_;

};

class LoadCommand : public Command {
public:
    LoadCommand(bool& running) : running_(running) {}
    void execute() override {
        running_ = false;
    }
private:
    bool& running_;

};

class LayoutCommand : public Command {
public:
    LayoutCommand(bool& running) : running_(running) {}
    void execute() override {
        running_ = false;
    }
private:
    bool& running_;

};

class ExportCommand : public Command {
public:
    ExportCommand(bool& running) : running_(running) {}
    void execute() override {
        running_ = false;
    }
private:
    bool& running_;

};

#endif
