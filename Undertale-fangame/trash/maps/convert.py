import json

data = dict()


input_file_path = input("Enter input file > ")
output_file_path = input_file_path[:input_file_path.rfind(".")] + ".csv"

with open(input_file_path, 'r') as file:
    data = json.load(file)

# CSV
# x1;y1;w1;h1;name1
# x2;y2;w2;h2;name2
output = ""

objects = dict()
layers = data["layers"]
for i in range(len(layers)):
    if layers[i]["name"].lower() == "colliders":
        objects = layers[i]["objects"]
        break

for obj in objects:
    data = str(obj["name"]).lower().split(':')
    
    name = data[0]
    spawn_position_x = None
    spawn_position_y = None
    next_action = None
    to_level = None

    if name == "new_action":
        next_action = data[1]

    if name == "level":
        spawn_position_x = data[1]
        spawn_position_y = data[2]
        to_level = data[3]

    if name == "area":
        output += f"""
            {name};{obj["width"]};{obj["height"]}
        """.strip()
        output += '\n'
        continue

    if spawn_position_x != None and spawn_position_y != None:
        output += f"""
            {name};{obj["x"]};{obj["y"]};{obj["width"]};{obj["height"]};{spawn_position_x};{spawn_position_y};{to_level}
        """.strip()
        output += '\n'
        continue
    
    if next_action != None:
        output += f"""
            {name};{obj["x"]};{obj["y"]};{obj["width"]};{obj["height"]};{next_action}
        """.strip()
        output += '\n'
        continue
    

    output += f"""
        {name};{obj["x"]};{obj["y"]};{obj["width"]};{obj["height"]}
    """.strip()
    output += '\n'

with open(output_file_path, 'w') as file:
    file.write(output.strip())

print("Done!")