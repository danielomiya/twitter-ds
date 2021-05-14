#!/usr/bin/env sh

# export variables to easier call them from python
export $(egrep -v '^#' .env | xargs -L 1)

# define useful variables
OUTPUT_FILE="data/out.csv"
PLACES=(
  "BRAZIL"
  "CANADA"
  "CHILE"
  "DENMARK"
  "FRANCE"
  "GERMANY"
  "INDIA"
  "MEXICO"
  "NETHERLANDS"
  "NEW_ZEALAND"
  "PORTUGAL"
  "UNITED_KINGDOM"
  "UNITED_STATES"
)

# function to avoid repetition
get_trends () {
  # WOEID aka WHERE ON EARTH ID
  woeid=$1
  echo "Getting trends data from $woeid"
  python3 scripts/twitter_service.py -o $OUTPUT_FILE --mode append --place $woeid
}

# remove file if it already exists
if [ -f "$OUTPUT_FILE" ]; then
  echo "Deleting current $OUTPUT_FILE"
  rm "$OUTPUT_FILE"
fi

for place in ${PLACES[*]}; do
  get_trends $place
done
