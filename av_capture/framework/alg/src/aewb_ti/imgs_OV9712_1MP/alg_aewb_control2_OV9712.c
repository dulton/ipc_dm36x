
#include "alg_aewb_priv.h"

extern awb_calc_data_t awb_calc_data_ov9712;
extern int   TI_2A_config_OV9712(int flicker_detection, int saldre);
extern short TI_2A_SetEEValues_OV9712(int shift_val);
extern int   TI_2A_ISP_control_OV9712(int eTime, int aGain, int dGain, int cTemp);
extern void  TI_2A_AE_config_OV9712(IAE_DynamicParams * aeDynamicParams, int min_exp, int step_size);
extern int   TI_fd_get_config_OV9712(int sensorMode, int* row_time, int* pinp, int* h3aWinHeight);
extern int   TI_fd_trigger_OV9712(IAEWB_Ae *curAe, IAEWB_Ae *nextAe);

void ALG_aewbSetExposureGain_OV9712(int EX, int AG, int DG, int init)
{
    if (init)
    {
        ALG_aewbSetSensorExposure(EX);
        ALG_aewbSetSensorGain(AG);
        ALG_aewbSetIsifDGain(DG);
    }
}  

static void TFC_Awb_OV9712(AWB_PARAM * awb_gain, int awb_mode)
{
    if (awb_mode == AWB_AUTO)
    {   
    }
    else if (awb_mode == OUTDOOR)
    {
        awb_gain->grGain += 6;
        awb_gain->gbGain += 6;
        awb_gain->rGain  += 6;
    }
    else if (awb_mode == INDOOR)
    {
        awb_gain->grGain -= 6;
        awb_gain->gbGain -= 6;
        awb_gain->bGain  -= 6;
    }
    else if (awb_mode == FLUORESCENT)
    {
        awb_gain->grGain -= 6;
        awb_gain->gbGain -= 6;
        awb_gain->rGain  -= 6;
    }
    else if(awb_mode == MANUAL)
    {
        awb_gain->rGain += (Aew_ext_parameter.iRedGain - 50)*3/2;
        awb_gain->bGain += (Aew_ext_parameter.iBlueGain - 50)*3/2;
    }
}

ALG_TI_Aewb_Priv TI_AWEB_OV9712 =
{
    .SetExposureGain = ALG_aewbSetExposureGain_OV9712,
    .SetEEValues     = TI_2A_SetEEValues_OV9712,
    .AE_config       = TI_2A_AE_config_OV9712,
    .ISP_control     = TI_2A_ISP_control_OV9712,
    .fd_get_config   = TI_fd_get_config_OV9712,
    .fd_trigger      = TI_fd_trigger_OV9712,
    .awb_adjust      = TFC_Awb_OV9712,
    .calc_data       = &awb_calc_data_ov9712
};

