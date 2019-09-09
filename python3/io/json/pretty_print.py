import json
from pprint import pprint

json_str = """
{"completed_in": 0.074,
"max_id": 264043230692245504,
"max_id_str": "264043230692245504",
"next_page": "?page=2&max_id=264043230692245504&q=python&rpp=5",
"page": 1,
"query": "python",
"refresh_url": "?since_id=264043230692245504&q=python",
"results": [{"created_at": "Thu, 01 Nov 2012 16:36:26 +0000",
            "from_user": "kun"
            }],
"results_per_page": 5,
"since_id": 0,
"since_id_str": "0"}
"""

d1 = json.loads(json_str)
pprint(d1)
