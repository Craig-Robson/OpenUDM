FROM python:3.8

RUN apt-get update && apt-get install -y swig

RUN mkdir /data && mkdir /data/outputs
RUN mkdir /openudm

WORKDIR /openudm

# add all relevant files to image
#COPY openudm scripts setup.py Data ./
COPY . .

RUN python setup.py build
RUN python setup.py install

# Run the model
CMD ["python", "scripts/udm_solo.py"]
