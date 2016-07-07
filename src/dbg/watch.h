#include "_global.h"
#include "command.h"
#include "expressionparser.h"
#include "jansson\jansson.h"
#include "..\bridge\bridgemain.h"

class WatchExpr
{
protected:
    char WatchName[MAX_WATCH_NAME_SIZE];
    ExpressionParser expr;
    WATCHDOGMODE watchdogMode;
    bool haveCurrValue;
    WATCHVARTYPE varType;
    duint currValue; // last result of getIntValue()

public:
    bool watchdogTriggered;
    unsigned int watchWindow;

    WatchExpr(const char* name, const char* expression, WATCHVARTYPE type);
    ~WatchExpr() {};
    duint getIntValue(); // evaluate the expression as integer
    bool modifyExpr(const char* expression, WATCHVARTYPE type); // modify the expression and data type
    void modifyName(const char* newName);

    inline WATCHDOGMODE getWatchdogMode()
    {
        return watchdogMode;
    };
    inline char* getName()
    {
        return WatchName;
    };
    inline void setWatchdogMode(WATCHDOGMODE mode)
    {
        watchdogMode = mode;
    };
    inline WATCHVARTYPE getType()
    {
        return varType;
    };
    inline duint getCurrIntValue()
    {
        return currValue;
    };
    inline const String & getExpr()
    {
        return expr.GetExpression();
    }
    inline const bool HaveCurrentValue()
    {
        return haveCurrValue;
    };
};

extern std::map<unsigned int, WatchExpr*> watchexpr;

void WatchClear();
unsigned int WatchAddExpr(const char* expr, WATCHVARTYPE type);
bool WatchModifyExpr(unsigned int id, const char* expr, WATCHVARTYPE type);
void WatchModifyName(unsigned int id, const char* newName);
void WatchDelete(unsigned int id);
void WatchSetWatchdogMode(unsigned int id, bool isEnabled);
bool WatchIsWatchdogTriggered(unsigned int id);
WATCHDOGMODE WatchGetWatchdogMode(unsigned int id);
duint WatchGetUnsignedValue(unsigned int id);
WATCHVARTYPE WatchGetType(unsigned int id);
std::vector<WATCHINFO> WatchGetList();

void WatchCacheSave(JSON root); // Save watch data to database
void WatchCacheLoad(JSON root); // Load watch data from database

CMDRESULT cbWatchdog(int argc, char* argv[]);
CMDRESULT cbAddWatch(int argc, char* argv[]);
CMDRESULT cbDelWatch(int argc, char* argv[]);
CMDRESULT cbSetWatchName(int argc, char* argv[]);
CMDRESULT cbSetWatchExpression(int argc, char* argv[]);
CMDRESULT cbSetWatchdog(int argc, char* argv[]);
