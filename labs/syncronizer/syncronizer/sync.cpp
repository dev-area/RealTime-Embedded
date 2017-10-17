// Search byte-wise for a sync pattern. As soon as the pattern is found, transition to
// frame-wise searching for confirming sync patterns
void Synchronizer::Searching_For_Sync_State::HandleByteStream(Synchronizer &m, char byte)
{
    if (byte == SYNC_PATTERN)
    {
       m.m_byteCounter = 0;
       m.m_goodSyncCounter = 0;
       m.ChangeState(&m.confirming_sync_state);
    }
}
   
// Perform a frame-wise search for the sync pattern. Go back to byte-wise frame search if
// even one expected sync is missed. If the frame-wise sync search finds expected number of
// sync patterns, move to the the in-sync state    
void Synchronizer::Confirming_Sync_Pattern_State::HandleByteStream(Synchronizer &m, char byte)
 {
     if (m.m_byteCounter == FRAME_SIZE)
     {
        m.m_byteCounter = 0;
            
        if (byte == SYNC_PATTERN)
        {
           if (++m.m_goodFrameCounter == GOOD_SYNC_THRESHOLD)
           {
              // We have detected the required number of
              // sync signals. So copy the sync byte and change
              // state to in sync
              m.m_frameBytes[m.m_byteCounter] = byte; 
              m.ChangeState(m.in_sync);
            }
        }
        else   // Expected sync pattern not found
        {
           // Since the expected sync pattern was not found, go back to
           // byte wise search for sync pattern
           
           m.ChangeState(&m.searching_for_sync_state);
        }
    }
}
    
// Keep receiving bytes and pass them to the higher layers when a frame has
// been completed. Even if one sync is detected to be bad, start checking
// for sync loss.
void Synchronizer::In_Sync_State::HandleByteStream(Synchronizer &m, char byte)
{
       
    if (m.m_byteCounter == FRAME_SIZE)
    {
       // Beginning of a new frame
       m.m_byteCounter = 0;
       m.PassFrameToHigherLayer(m.m_frameBytes);         
       if (byte != SYNC_PATTERN)
       {
           m.m_badSyncCounter = 1;
           m.ChangeState(m.confirming_sync_loss_state);
       }
    }           
    m.m_frameBytes[m.m_byteCounter++] = byte;        
}
   
// Check for sync loss. If a given consecutive bad sync threshold is exceeded, transition
// to the unsynchronized state and perform a byte wise search for the sync pattern.    
void Synchronizer::Confirming_Sync_Loss_State::HandleByteStream(Synchronizer &m, char byte)
{
     if (m.m_byteCounter == FRAME_SIZE)
     {
        m.m_byteCounter = 0;
            
        if (byte != SYNC_PATTERN)
        {
           if (++m.m_badFrameCounter == BAD_SYNC_THRESHOLD)
           {
              // Too many sync misses have been detected.
              // Moving to out of sync state           
              m.ChangeState(&m.searching_for_sync_state);
           }
        }
        else   // Expected sync pattern is found
        {
           // Since the expected sync pattern was found, go back to
           // the in sync state
           m.ChangeState(&m.in_sync_state);
        }
    }    
    m.m_frameBytes[m.m_byteCounter++] = byte;       
} 