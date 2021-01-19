import pandas as pd

old_scale_df = pd.read_csv("input_scaling_new_with_old_format.csv")

new_df = old_scale_df.rename(rows={"RAINRATE": "Precip_rate", "Q2D" : "SPFH_2maboveground_kg_per_kg", "T2D" : "TMP_2maboveground_K", "LWDOWN" : "DLWRF_surface_W_per_meters_squared", "SWDOWN" : "DSWRF_surface_W_per_meters_squared", "PSFC" : "PRES_surface_Pa", "U2D" : "UGRD_10maboveground_meters_per_second", "V2D" : "VGRD_10maboveground_meters_per_second", "area_sqkm" : "Area_Square_km", "lat" : "Latitude", "lon" : "Longitude"})

new_df.to_csv("input_scaling.csv", index=False)

