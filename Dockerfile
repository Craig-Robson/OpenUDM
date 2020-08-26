FROM python:3.8

RUN apt-get update && apt-get install -y swig

# add all relevant files to image
ADD src/ /openudm/openudm
ADD scripts/ /openudm/scripts
ADD setup.py /openudm/setup.py

# this should be replaced once pulling data from NID or NISMOD-DB API
ADD Data/ /openudm/Data

# create a directory to store the outputs
RUN mkdir /data && mkdir /data/outputs && mkdir /data/inputs

WORKDIR /openudm

RUN python setup.py build
RUN python setup.py install

# Run the model
CMD ["python", "scripts/udm_solo.py"]
