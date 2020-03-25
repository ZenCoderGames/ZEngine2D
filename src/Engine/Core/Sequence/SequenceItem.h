//
// Created by srinavinnair on 3/14/20.
//

#ifndef ZCOREENGINE_SEQUENCEITEM_H
#define ZCOREENGINE_SEQUENCEITEM_H

#include <functional>

class SequenceItem {
private:
    bool m_hasExecuted;
    std::function<void()> m_funcToExecute;
    float m_executeTime;
public:
    SequenceItem(std::function<void()> funcToExecute, float executeTime) {
        m_funcToExecute = funcToExecute;
        m_executeTime = executeTime;
        m_hasExecuted = false;
    }

    bool CanExecute(float elapsedTime) {
        return !m_hasExecuted && elapsedTime>=m_executeTime;
    }

    void Execute() {
        m_hasExecuted = true;
        if(m_funcToExecute)
            m_funcToExecute();
    }

    bool HasExecuted() {
        return m_hasExecuted;
    }
};

#endif //ZCOREENGINE_SEQUENCEITEM_H
