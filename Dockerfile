FROM python:3.8

RUN apt-get update && apt-get install -y swig

RUN mkdir /data/outputs/openudm

WORKDIR /data/outputs/openudm

# add all relevant files to image
COPY src scripts setup.py Data .

RUN python setup.py build
RUN python setup.py install

# Run the model
CMD ["python", "scripts/udm_solo.py"]
