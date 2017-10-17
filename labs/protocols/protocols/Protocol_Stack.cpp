#include "Protocol_Stack.h"
#include "Protocol_Layer.h"
#include <assert.h>


void Protocol_Stack::Handle_Transmit(Protocol_Packet *p_Packet)
{
    if (m_p_Highest_Layer)
    {
        m_p_Highest_Layer->Transmit(p_Packet);
    }
}


void Protocol_Stack::Handle_Receive(Protocol_Packet *p_Packet)
{
    if (m_p_Lowest_Layer)
    {
        m_p_Lowest_Layer->Handle_Receive(p_Packet);
    }
}


void Protocol_Stack::Add_Layer(Protocol_Layer *p_Layer, Placement placement, Protocol_Layer *p_Existing_Layer)
{
    // Start with a clean slate. Initialize the upper and lower protocol
    // layers to NULL. The pointers will be suitably initialized after insertion.

    p_Layer->Set_Lower_Layer(NULL);
    p_Layer->Set_Upper_Layer(NULL);

    // Check if some other layer is already present in the protocol stack. 
    // The placement processing applies only if this is not the first layer 
    // being added to the stack.
    if (m_p_Highest_Layer)
    {
        // This is not the first layer

        switch (placement)
        {
        case TOP:   // Add the layer at the top
            assert(p_Existing_Layer == NULL);
            m_p_Highest_Layer->Set_Upper_Layer(p_Layer);
            p_Layer->Set_Lower_Layer(m_p_Highest_Layer);
            m_p_Highest_Layer = p_Layer;
            break;

        case ABOVE: // Place the layer above the existing layer
            assert(p_Existing_Layer);

            Protocol_Layer *p_Previous_Upper_Layer;

            // Linking up the new layer above the existing layer
            p_Previous_Upper_Layer = p_Existing_Layer->Get_Upper_Layer();
            p_Layer->Set_Upper_Layer(p_Previous_Upper_Layer);
            p_Layer->Set_Lower_Layer(p_Existing_Layer);
            p_Existing_Layer->Set_Upper_Layer(p_Layer);

            // Check if the existing layer was the highest layer
            if (p_Existing_Layer == m_p_Highest_Layer)
            {
                // If it was, make the new layer the highest layer
                m_p_Highest_Layer = p_Layer;
            }
            else
            {
                // Change the pointer of the existing layer's upper layer
                // to point to the newly inserted layer.
                p_Previous_Upper_Layer->Set_Lower_Layer(p_Layer);
            }
            break;

        case BELOW:    // Place the layer below the existing layer

            assert(p_Existing_Layer);
            Protocol_Layer *p_Previous_Lower_Layer;

            // Linking up the new layer below the existing layer
            p_Previous_Lower_Layer = p_Existing_Layer->Get_Lower_Layer();
            p_Layer->Set_Upper_Layer(p_Existing_Layer);
            p_Layer->Set_Lower_Layer(p_Previous_Lower_Layer);
            p_Existing_Layer->Set_Lower_Layer(p_Layer);

            // Check if the existing layer was the lowest layer
            if (p_Existing_Layer == m_p_Lowest_Layer)
            {
                // If it was, make the new layer the lowest layer
                m_p_Lowest_Layer = p_Layer;
            }
            else
            {
                // Change the pointer of the existing layer's lower layer
                // to point to the newly inserted layer.
                p_Previous_Lower_Layer->Set_Upper_Layer(p_Layer);
            }
            break;

        }
    }
    else  // The highest layer is NULL
    {
        // This means that this is the first layer in the protocol stack.
        assert(p_Existing_Layer == NULL);
        m_p_Highest_Layer = p_Layer;
        m_p_Lowest_Layer = p_Layer;
    }
}


void Protocol_Stack::Remove_Layer(Protocol_Layer *p_Layer)
{
    // Check if the layer to be removed is the highest layer.
    if (p_Layer == m_p_Highest_Layer)
    {
        // Yes it is, so set the removed layer's lower layer as the highest layer
        // in the protocol stack.
        m_p_Highest_Layer = p_Layer->Get_Lower_Layer();

        // If this was not the only layer in the stack, set the
        // upper layer of this layer as NULL.
        if (m_p_Highest_Layer)
        {
            m_p_Highest_Layer->Set_Upper_Layer(NULL);
        }
    }
    else // Not the highest layer
    {
        // Stitch the upper layer to lower layer link after the layer is removed.
        (p_Layer->Get_Upper_Layer())->Set_Lower_Layer(p_Layer->Get_Lower_Layer());
    }

    // Check if the layer to be removed is the lowest layer.
    if (p_Layer == m_p_Lowest_Layer)
    {
        // Yes it is, so set the removed layer's upper layer as the lowest layer
        // in the protocol stack.
        m_p_Lowest_Layer = p_Layer->Get_Upper_Layer();

        // If this was not the only layer in the stack, set the
        // lower layer of this layer as NULL.
        if (m_p_Lowest_Layer)
        {
            m_p_Lowest_Layer->Set_Lower_Layer(NULL);
        }
    }
    else
    {
        // Stitch the lower layer to upper layer link after the layer is removed.
        (p_Layer->Get_Lower_Layer())->Set_Upper_Layer(p_Layer->Get_Upper_Layer());
    }

    // Set the upper and lower layer pointers of the removed layer as NULL.
    // This is a safety measure.
    p_Layer->Set_Lower_Layer(NULL);
    p_Layer->Set_Upper_Layer(NULL);
}


Protocol_Stack::Protocol_Stack()
{
    m_p_Highest_Layer = NULL;
    m_p_Lowest_Layer = NULL;
}
