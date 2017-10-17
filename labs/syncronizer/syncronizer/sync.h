class Synchronizer
{
private:
    // Counter incremented when a good sync pattern is detected in an out of sync state
    int m_goodSyncCounter;
    
    // Counter incremented when a sync loss is detected in an in sync state
    int m_badSyncCounter;
    
    // Counter used to keep track of sync periodicity. Reset whenever a sync pattern
    // is detected.
    int m_byteCounter;

    // Array for storing the frame contents
    char m_frameBytes[FRAME_SIZE];
    
    friend class Base_State;
    friend class Unsynchronized;
    friend class Synchronized;
    friend class Searching_For_Sync_State;
    friend class Confirming_Sync_Pattern_State;
    friend class In_Sync_State;
    friend class Confirming_Sync_Loss_State;
         
    // Abstract base class for all states
    class Base_State
    {
        void HandleByteStream(Synchronizer &m, char byte) = 0;
    };
    
    class Unsynchronized : public Base_State
    {
       // Common handling for all unsynchronized states should be here
    };
    
    class Synchronized : public Base_State
    {  
      // Common handling for all synchronized states should be here
    };
     
    class Searching_For_Sync_State : public Unsynchronized
    {
        void HandleByteStream(Synchronizer &m, char byte);
    };
    
    class Confirming_Sync_Pattern_State : public Unsynchronized
    {
        void HandleByteStream(Synchronizer &m, char byte);
 
    };

    class In_Sync_State : public Synchronized
    {
        void HandleByteStream(Synchronizer &m, char byte);
    };
    
    class Confirming_Sync_Loss_State : public Synchronized
    {
        void HandleByteStream(Synchronizer &m, char byte);
    };
    
    static Searching_For_Sync_State searching_for_sync_state;
    static Confirming_Sync_Pattern_State confirming_sync_pattern_state;
    static In_Sync_State in_sync_state;
    static Confirming_Sync_Loss_State confirming_sync_loss_state;

    Base_State *m_pCurrentState;
    
    void ChangeState(Base_State *pNextState)
    {
       m_pCurrentState = m_pNextState;
    }
    // Pass Frame to higher layer .Pointer to the beginning of the frame
    // is passed (Sync pattern is included)
    void PassFrameToHigherLayer(const char *pFrameData);
public:

    // Handle a byte aligned stream. In this example, the sync pattern
    // is defined at byte boundaries.
    void HandleByteStream(char byte)
    {
        // Pass the byte to the currently active state
        m_pCurrentState->HandleByteStream(Synchronizer &m, char byte);
    }
    
};
