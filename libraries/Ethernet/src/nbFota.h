#ifndef FOTA_H_
#define FOTA_H_

// NOT READY

#include <Arduino.h>

typedef void (*fota_callback)(fota_msg_event_t, fota_msg_event_info_t *);
extern "C" uint32_t fota_register_event(fota_callback call_back);
extern "C" fota_result_t fota_download_image(fota_image_t image, char *image_uri);
extern "C" fota_result_t fota_trigger_upgrade(fota_image_t image);
extern "C" void fota_set_current_state(fota_state_t state);

extern int g_fota_result;

class FOTA
{
  private:
  public:
    FOTA() {}

    bool begin(fota_callback userCallback)
    {
        return userCallback && fota_register_event(userCallback) != 0;
    }

    bool start(const char *url)
    {
        return url && fota_download_image(FOTA_MAIN_BIN, (char *)url) == FOTA_OK;
    }

    void cancel()
    {
        fota_set_current_state(FOTA_IDLE);
    }

    bool download(const char *url)
    {
        if (fota_register_event(m_download_cb))
            return url && fota_download_image(FOTA_MAIN_BIN, (char *)url) == FOTA_OK;
        return false;
    }

  private:
    static void m_download_cb(fota_msg_event_t event, fota_msg_event_info_t *info)
    {
        if (event > FOTA_MSG_DOWNLOAD_PROGRESS_IND)
        {
            fota_set_current_state(FOTA_IDLE); // cancel
            g_fota_result = info->fota_result;
        }
    }
};

#endif