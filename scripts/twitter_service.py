import argparse
import csv
import os
from enum import Enum
from typing import Union

import requests

TWITTER_V1_1_BASE_URL = "https://api.twitter.com/1.1/"
DEFAULT_OUTPUT_FILE = "data/out.csv"


class WOEID(Enum):
    BRAZIL = 23424768
    CANADA = 23424775
    UNITED_KINGDOM = 23424975
    UNITED_STATES = 23424977


class TwitterService:
    def __init__(
        self,
        consumer_key: str = os.getenv("TWITTER_CONSUMER_KEY"),
        consumer_secret: str = os.getenv("TWITTER_CONSUMER_SECRET"),
        access_token: str = os.getenv("TWITTER_ACCESS_TOKEN"),
        token_secret: str = os.getenv("TWITTER_TOKEN_SECRET"),
        bearer_token: str = os.getenv("TWITTER_BEARER_TOKEN"),
    ):
        self.consumer_key = consumer_key
        self.consumer_secret = consumer_secret
        self.access_token = access_token
        self.token_secret = token_secret
        self.bearer_token = bearer_token

        session = requests.Session()
        session.headers.update({"Authorization": f"Bearer {bearer_token}"})
        self._session = session

    def get_trends_by_place(self, place: Union[int, WOEID]) -> list:
        if isinstance(place, WOEID):
            place = place.value

        response = self._session.get(
            f"{TWITTER_V1_1_BASE_URL}trends/place.json?id={place}"
        )
        return response.json()[0]["trends"]


def get_args():
    parser = argparse.ArgumentParser(description="Gets Twitter trends")
    parser.add_argument(
        "--place", type=int, default=WOEID.BRAZIL, help="place to get trends from"
    )
    parser.add_argument(
        "--output", "-o", default=DEFAULT_OUTPUT_FILE, help="write output to file"
    )
    return parser.parse_args()


if __name__ == "__main__":
    args = get_args()
    twitter = TwitterService()
    trends = twitter.get_trends_by_place(args.place)

    with open(args.output, "w", newline="") as f:
        field_names = ["name", "url", "promoted_content", "query", "tweet_volume"]
        writer = csv.DictWriter(
            f, field_names, delimiter=";", quoting=csv.QUOTE_MINIMAL
        )
        writer.writeheader()

        for trend in trends:
            if trend["tweet_volume"] is not None:
                writer.writerow(trend)
