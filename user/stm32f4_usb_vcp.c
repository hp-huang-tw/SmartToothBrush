#include "stm32f4_usb_vcp.h"
#include "usbd_usr.h"

uint8_t INT_USB_VCP_ReceiveBuffer[USB_VCP_RECEIVE_BUFFER_LENGTH];
uint32_t int_usb_vcp_buf_in, int_usb_vcp_buf_out, int_usb_vcp_buf_num;
extern USB_VCP_Result USB_VCP_INT_Status;
uint8_t USB_VCP_INT_Init = 0;

USB_OTG_CORE_HANDLE	USB_OTG_dev;

/* USB VCP Internal receive buffer */
extern uint8_t INT_USB_VCP_ReceiveBuffer[USB_VCP_RECEIVE_BUFFER_LENGTH];


USB_VCP_Result USB_VCP_Init(void) {
	/* Initialize USB */
	USBD_Init(	&USB_OTG_dev,
#ifdef USE_USB_OTG_FS
				USB_OTG_FS_CORE_ID,
#else
				USB_OTG_HS_CORE_ID,
#endif
				&USR_desc, 
				&USBD_CDC_cb, 
				&USR_cb);
	
	/* Reset buffer counters */
	int_usb_vcp_buf_in = 0;
	int_usb_vcp_buf_out = 0;
	int_usb_vcp_buf_num = 0;
	
	/* Initialized */
	USB_VCP_INT_Init = 1;
	
	/* Return OK */
	return USB_VCP_OK;
}

USB_VCP_Result USB_VCP_Getc(uint8_t* c) {
	/* Any data in buffer */
	if (int_usb_vcp_buf_num > 0) {
		/* Check overflow */
		if (int_usb_vcp_buf_out >= USB_VCP_RECEIVE_BUFFER_LENGTH) {
			int_usb_vcp_buf_out = 0;
		}
		*c = INT_USB_VCP_ReceiveBuffer[int_usb_vcp_buf_out];
		INT_USB_VCP_ReceiveBuffer[int_usb_vcp_buf_out] = 0;
		
		/* Set counters */
		int_usb_vcp_buf_out++;
		int_usb_vcp_buf_num--;
		
		/* Data OK */
		return USB_VCP_DATA_OK;
	}
	*c = 0;
	/* Data not ready */
	return USB_VCP_DATA_EMPTY;
}

USB_VCP_Result USB_VCP_Gets(char* buffer, uint8_t bufsize) {
	uint16_t i = 0;                             
	uint8_t eol = 0;
	uint8_t c;
	if (USB_VCP_Getc(&c) != USB_VCP_DATA_OK) {
		return USB_VCP_DATA_EMPTY;
	}
	if (bufsize > 0) {
		buffer[i++] = (char) c;
		while (!eol) {
			while (USB_VCP_Getc(&c) != USB_VCP_DATA_OK);
			buffer[i] = (char) c;   
			if (buffer[i] == '\n') {
				eol = 1;                
			} else {            
				if (i < (bufsize - 1)) {
					i++; 	
				}
			}
		}
		/* Add zero to the end of string */
		buffer[i] = 0;               
	}
	/* Data ok */
	return USB_VCP_DATA_OK;
}

USB_VCP_Result USB_VCP_Putc(volatile char c) {
	uint8_t ce = (uint8_t)c;
	/* Send data over USB */
	VCP_DataTx(&ce, 1);
	
	/* Return OK */
	return USB_VCP_OK;
}

USB_VCP_Result USB_VCP_Puts(char* str) {
	while (*str) {
		USB_VCP_Putc(*str++);
	}
	
	/* Return OK */
	return USB_VCP_OK;
}

USB_VCP_Result INT_USB_VCP_AddReceived(uint8_t c) {
	/* Still available data in buffer */
	if (int_usb_vcp_buf_num < USB_VCP_RECEIVE_BUFFER_LENGTH) {
		/* Check for overflow */
		if (int_usb_vcp_buf_in >= USB_VCP_RECEIVE_BUFFER_LENGTH) {
			int_usb_vcp_buf_in = 0;
		}
		/* Add character to buffer */
		INT_USB_VCP_ReceiveBuffer[int_usb_vcp_buf_in] = c;
		/* Increase counters */
		int_usb_vcp_buf_in++;
		int_usb_vcp_buf_num++;
		
		/* Return OK */
		return USB_VCP_OK;
	}
	/* Return Buffer full */
	return USB_VCP_RECEIVE_BUFFER_FULL;
}

USB_VCP_Result USB_VCP_GetStatus(void) {
	if (USB_VCP_INT_Init) {
		return USB_VCP_INT_Status;
	}
	return USB_VCP_ERROR;
}

