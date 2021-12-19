#ifndef __protoreadwrite_h__
#define __protoreadwrite_h__

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "bank.h"
#include "user.h"
#include "account.h"
#include "transaction.h"
#include "../bank.pb.h"

using namespace std;

// making my data access class a static class
class ProtoReadWrite {
    private:
        
    public:
        static void writeToDisk(Bank*);
        static Bank* readFromDisk(void);
};

#endif