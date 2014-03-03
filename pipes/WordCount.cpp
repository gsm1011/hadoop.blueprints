#include <algorithm> 
#include <limits> 
#include <string> 
#include <vector>
#include "stdint.h" 
#include "Pipes.hh"
#include "TemplateFactory.hh" 
#include "StringUtils.hh" 

class WordCountMap : public HadoopPipes::Mapper {
public: 
    // WordCountMap() {}
    WordCountMap(HadoopPipes::TaskContext& context) {}
    ~WordCountMap() {}
    
    void map(HadoopPipes::MapContext& context) {
        std::string line = context.getInputValue(); 
        std::vector<std::string> words = HadoopUtils::splitString(line, " "); 

        // emit the tuples. 
        for(unsigned i = 0; i < words.size(); i++) {
            context.emit(words[i], "1"); 
        }
    }
};

class WordCountReduce : public HadoopPipes::Reducer {
public:
    //    WordCountReduce() {}
    WordCountReduce(HadoopPipes::TaskContext& context) {} 
    ~WordCountReduce(void) {}

    void reduce(HadoopPipes::ReduceContext& context) {

        int cnt = 0; 
        while(context.nextValue()) {
            cnt += HadoopUtils::toInt(context.getInputValue()); 
        }

        context.emit(context.getInputKey(), HadoopUtils::toString(cnt)); 
    }
};

int main(int argc, char** argv) {
    return HadoopPipes::runTask(HadoopPipes::TemplateFactory<WordCountMap, WordCountReduce>());

    return 0; 
}
