//
// Created by srinavinnair on 3/14/20.
//

#ifndef ZCOREENGINE_SEQUENCE_H
#define ZCOREENGINE_SEQUENCE_H

#include <vector>
#include "./SequenceItem.h"

class Sequence {
private:
    unsigned int m_startTime;
    float m_completionTime;
    bool m_isStarted, m_isCompleted;
    std::vector<SequenceItem*> m_sequenceItemList;
    std::function<void()> m_onCompleteFunc;
public:
    Sequence(std::function<void()> onCompleteFunc, float completionTime) {
        m_onCompleteFunc = onCompleteFunc;
        m_completionTime = completionTime;
    }

    void AddSequenceItem(std::function<void()> funcToExecute, float executeTime) {
        m_sequenceItemList.push_back(new SequenceItem(funcToExecute, executeTime));
    }

    void Start() {
        m_isStarted = true;
        m_isCompleted = false;
        m_startTime = SDL_GetTicks();
    }

    bool IsStarted() {
        return m_isStarted;
    }

    bool IsCompleted() {
        return m_isCompleted;
    }

    void Update() {
        if(m_isCompleted)
            return;

        if(m_isStarted) {
            float currentTime = static_cast<float>(SDL_GetTicks() - m_startTime)/1000;

            for(auto sequenceItem : m_sequenceItemList) {
                if(sequenceItem->CanExecute(currentTime)) {
                    sequenceItem->Execute();
                }
            }

            if(currentTime >= m_completionTime) {
                m_isCompleted = true;
                if(m_onCompleteFunc)
                    m_onCompleteFunc();
            }
        }
    }
};

#endif //ZCOREENGINE_SEQUENCE_H
