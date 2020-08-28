# OpenUDM
Open repository for the Urban Development Model

# Deploying on DAFNI
 - build and save docker container as .tar.gz
 - model_definition_file.yml stores the metadata required by DAFNI to store and set up the model for use on the platform
 
# Changes made for DAFNI version

28/8/2020
- Dockerfile and runs script updated so outputs stored in /data/outputs/* directory
- run script (in scripts directory) expects to pull the initial zone population and final zone population from environmental vairables. To limit changes the run script re-writes the input csv which the model uses with these values
