/*******************************************************************************
* File Name: LineInterrupt.c  
* Version 1.60
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <LineInterrupt.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START LineInterrupt_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: LineInterrupt_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void LineInterrupt_Start(void)
{
    /* For all we know the interrupt is active. */
    LineInterrupt_Disable();

    /* Set the ISR to point to the LineInterrupt Interrupt. */
    LineInterrupt_SetVector(LineInterrupt_Interrupt);

    /* Set the priority. */
    LineInterrupt_SetPriority(LineInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LineInterrupt_Enable();
}

/*******************************************************************************
* Function Name: LineInterrupt_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void LineInterrupt_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    LineInterrupt_Disable();

    /* Set the ISR to point to the LineInterrupt Interrupt. */
    LineInterrupt_SetVector(address);

    /* Set the priority. */
    LineInterrupt_SetPriority(LineInterrupt_INTC_PRIOR_NUMBER);

    /* Enable it. */
    LineInterrupt_Enable();
}

/*******************************************************************************
* Function Name: LineInterrupt_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void LineInterrupt_Stop(void) 
{
    /* Disable this interrupt. */
    LineInterrupt_Disable();
}

/*******************************************************************************
* Function Name: LineInterrupt_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for LineInterrupt.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(LineInterrupt_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START LineInterrupt_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (LineInterrupt__ES2_PATCH ))      
            LineInterrupt_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: LineInterrupt_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling LineInterrupt_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use LineInterrupt_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LineInterrupt_SetVector(cyisraddress address) 
{
    CY_SET_REG16(LineInterrupt_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: LineInterrupt_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress LineInterrupt_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(LineInterrupt_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: LineInterrupt_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling LineInterrupt_Start
*   or LineInterrupt_StartEx will override any effect this method would have had. 
*	This method should only be called after LineInterrupt_Start or 
*	LineInterrupt_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LineInterrupt_SetPriority(uint8 priority) 
{
    *LineInterrupt_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: LineInterrupt_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 LineInterrupt_GetPriority(void) 
{
    uint8 priority;


    priority = *LineInterrupt_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: LineInterrupt_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LineInterrupt_Enable(void) 
{
    /* Enable the general interrupt. */
    *LineInterrupt_INTC_SET_EN = LineInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LineInterrupt_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 LineInterrupt_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*LineInterrupt_INTC_SET_EN & LineInterrupt__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: LineInterrupt_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LineInterrupt_Disable(void) 
{
    /* Disable the general interrupt. */
    *LineInterrupt_INTC_CLR_EN = LineInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LineInterrupt_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LineInterrupt_SetPending(void) 
{
    *LineInterrupt_INTC_SET_PD = LineInterrupt__INTC_MASK;
}

/*******************************************************************************
* Function Name: LineInterrupt_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void LineInterrupt_ClearPending(void) 
{
    *LineInterrupt_INTC_CLR_PD = LineInterrupt__INTC_MASK;
}
