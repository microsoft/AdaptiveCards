debug_string_test = [
    'item(1)\n', 'item(1)\n', 'item(1)\n', 'item(1)\n', 'item(1)\n',
    'item(1)\n', 'row\n', '\tcolumn\n', '\t\titem(1)\n', '\tcolumn\n',
    '\t\titem(1)\n', 'row\n', '\tcolumn\n', '\t\titem(1)\n', '\tcolumn\n',
    '\t\titem(5)\n', '\tcolumn\n', '\t\titem(1)\n', 'item(1)\n', 'item(1)\n',
    'item(1)\n', 'item(1)\n', 'row\n', '\tcolumn\n', '\t\titem(1)\n',
    '\tcolumn\n', '\t\titem(5)\n', '\tcolumn\n', '\t\titem(1)\n', 'row\n',
    '\tcolumn\n', '\t\titem(1)\n', '\tcolumn\n', '\t\titem(1)\n'
]
# image - training images 5.png
test_img_obj1 = [259.61538419127464, 93.91641104221344,
                 363.92310082912445, 198.15856432914734]

test_img_obj2 = [143.74213486909866, 95.04049408435822,
                 248.02349030971527, 197.5490162372589]

# Choiceset Grouping test image 100
test_cset_obj1 = [13.708709377795458, 206.46938413381577,
                  155.36615484952927, 227.09414440393448]

test_cset_obj2 = [16.655487801879644, 227.20616340637207,
                  165.07373866438866, 245.98763144016266]

# sample design_objects
mock_desing_obj = [
    {
        "object": "textbox",
        "xmin": 24.699735146015882,
        "ymin": 162.31396371126175,
        "xmax": 103.7798099219799,
        "ymax": 181.99412715435028,
        "coords": (
            24.699735146015882,
            162.31396371126175,
            103.7798099219799,
            181.99412715435028,
        ),
        "score": 0.9638245,
        "uuid": "a966ba72-851e-4335-a073-97a4b68ff3cd",
        "class": 1,
        "horizontal_alignment": "Left",
        "data": "2 Stops",
        "image_data": {
            "level": [1, 2, 3, 4, 5, 5],
            "page_num": [1, 1, 1, 1, 1, 1],
            "block_num": [0, 1, 1, 1, 1, 1],
            "par_num": [0, 0, 1, 1, 1, 1],
            "line_num": [0, 0, 0, 1, 1, 1],
            "word_num": [0, 0, 0, 0, 1, 2],
            "left": [0, 10, 10, 10, 10, 25],
            "top": [0, 5, 5, 5, 5, 5],
            "width": [89, 64, 64, 64, 8, 49],
            "height": [20, 15, 15, 15, 13, 15],
            "conf": ["-1", "-1", "-1", "-1", 86, 86],
            "text": ["", "", "", "", "2", "Stops"],
            "uuid": "a966ba72-851e-4335-a073-97a4b68ff3cd",
        },
        "size": "Small",
        "weight": {"a966ba72-851e-4335-a073-97a4b68ff3cd": 2.51},
        "color": "Dark",
    },
]

# design_objects for Approvals_image
mock_desing_obj_eq_weight = [
    {
        "object": "textbox",
        "xmin": 14.52466070652008,
        "ymin": 11.586663722991943,
        "xmax": 98.29278087615967,
        "ymax": 33.354628562927246,
        "coords": (
            14.52466070652008,
            11.586663722991943,
            98.29278087615967,
            33.354628562927246,
        ),
        "score": 0.9995384,
        "uuid": "9b473ea0-0408-40c4-a99f-1b2e0427ec1d",
        "class": 1,
        "horizontal_alignment": "Left",
        "data": "Approvals",
        "image_data": {
            "level": [1, 2, 3, 4, 5],
            "page_num": [1, 1, 1, 1, 1],
            "block_num": [0, 1, 1, 1, 1],
            "par_num": [0, 0, 1, 1, 1],
            "line_num": [0, 0, 0, 1, 1],
            "word_num": [0, 0, 0, 0, 1],
            "left": [0, 11, 11, 11, 11],
            "top": [0, 5, 5, 5, 5],
            "width": [93, 71, 71, 71, 71],
            "height": [21, 15, 15, 15, 15],
            "conf": ["-1", "-1", "-1", "-1", 83],
            "text": ["", "", "", "", "Approvals"],
            "uuid": "9b473ea0-0408-40c4-a99f-1b2e0427ec1d",
        },
        "size": "ExtraLarge",
        "weight": {"9b473ea0-0408-40c4-a99f-1b2e0427ec1d": 1.03},
        "color": "Dark",
    },
    {
        "object": "textbox",
        "xmin": 110.8454418182373,
        "ymin": 103.87897300720215,
        "xmax": 322.5535640716553,
        "ymax": 134.351713180542,
        "coords": (
            110.8454418182373,
            103.87897300720215,
            322.5535640716553,
            134.351713180542,
        ),
        "score": 0.99614584,
        "uuid": "4ed3ed20-3f2a-41e6-9c96-435476fe2422",
        "class": 1,
        "horizontal_alignment": "Center",
        "data": "Pending Approvals",
        "image_data": {
            "level": [1, 2, 3, 4, 5, 5],
            "page_num": [1, 1, 1, 1, 1, 1],
            "block_num": [0, 1, 1, 1, 1, 1],
            "par_num": [0, 0, 1, 1, 1, 1],
            "line_num": [0, 0, 0, 1, 1, 1],
            "word_num": [0, 0, 0, 0, 1, 2],
            "left": [0, 13, 13, 13, 13, 104],
            "top": [0, 4, 4, 4, 4, 4],
            "width": [222, 193, 193, 193, 82, 102],
            "height": [30, 23, 23, 23, 23, 22],
            "conf": ["-1", "-1", "-1", "-1", 96, 96],
            "text": ["", "", "", "", "Pending", "Approvals"],
            "uuid": "4ed3ed20-3f2a-41e6-9c96-435476fe2422",
        },
        "size": "ExtraLarge",
        "weight": {"4ed3ed20-3f2a-41e6-9c96-435476fe2422": 1.03},
        "color": "Dark",
    },
]
