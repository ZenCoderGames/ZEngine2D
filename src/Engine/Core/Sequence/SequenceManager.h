//
// Created by srinavinnair on 3/14/20.
//

#ifndef ZCOREENGINE_SEQUENCEMANAGER_H
#define ZCOREENGINE_SEQUENCEMANAGER_H

#include "./Sequence.h"

class SequenceManager {
private:
    std::vector<Sequence*> m_sequenceList;
public:
    void Update() {
        for(int i=0; i<m_sequenceList.size(); ++i) {
            if(m_sequenceList[i]->IsStarted()) {
                m_sequenceList[i]->Update();
                if (m_sequenceList[i]->IsCompleted()) {
                    m_sequenceList.erase(m_sequenceList.begin() + i);
                    i--;
                }
            }
        }
    }

    Sequence* CreateSequence(std::function<void()> onCompleteFunc, float completionTime) {
        Sequence* newSequence = new Sequence(onCompleteFunc, completionTime);
        m_sequenceList.push_back(newSequence);
        return newSequence;
    }
};

#endif //ZCOREENGINE_SEQUENCEMANAGER_H
