import pandas as pd

ct_df = pd.read_csv("c_t_start.csv")

ht_df = pd.read_csv("h_t_start.csv")

ct_df2 = ct_df.rename(columns={"0": "c_t"})
ht_df2 = ht_df.rename(columns={"0": "h_t"})

combined_df = pd.concat([ht_df2, ct_df2], axis=1, join="inner")


combined_df2 = combined_df.drop(columns=["Unnamed: 0", "Unnamed: 0"])

combined_df2.to_csv("initial_states.csv", index=False)

