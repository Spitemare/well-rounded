#include "logging.h"
#include "settings.h"

Settings *settings_load() {
    logd("%s", __func__);
    Settings *settings = malloc(sizeof(Settings));

    int32_t version = persist_read_int(SETTINGS_VERSION_KEY);
    if (version == 0) {
        settings->color_background = GColorBlack;
        settings->color_ticks = GColorLightGray;
        settings->color_hour_hand = PBL_IF_COLOR_ELSE(GColorRed, GColorWhite);
        settings->color_minute_hand = GColorLightGray;
        settings->color_second_hand = GColorWhite;
        settings->color_battery = PBL_IF_COLOR_ELSE(GColorIslamicGreen, GColorLightGray);
        settings->show_ticks = true;
        settings->show_second_hand = false;
        settings->show_battery = true;
#ifdef PBL_HEALTH
        settings->color_health = GColorBlueMoon;
        settings->show_health = true;
#endif
#ifdef PBL_COLOR
        settings->color_connection_lost = GColorIndigo;
        settings->vibe_connection_lost = ConnectionVibeDisconnect;
#endif
        settings->color_date = GColorWhite;
        settings->direction_date = DateEast;
        settings->show_date = true;
        settings_save(settings);
    } else {
        persist_read_data(SETTINGS_DATA_KEY, settings, sizeof(Settings));
    }

    if (version == 1) {
        persist_read_data(SETTINGS_DATA_KEY, settings, sizeof(Settings));
        settings->color_date = GColorWhite;
        settings->direction_date = DateEast;
        settings->show_date = true;
        settings_save(settings);
    }
    return settings;
}

void settings_save(Settings *this) {
    logd("%s", __func__);
    persist_write_int(SETTINGS_VERSION_KEY, SETTINGS_VERSION);
    persist_write_data(SETTINGS_DATA_KEY, this, sizeof(Settings));
}

void settings_free(Settings *this) {
    logd("%s", __func__);
    free(this);
}
