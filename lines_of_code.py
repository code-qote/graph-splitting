import os

extensions = ['cpp', 'h']

res = dict()

for path, subdirs, files in os.walk(os.getcwd()):
    for name in files:
        for ext in extensions:
            if name[-len(ext):] == ext:
                p = os.path.join(path, name)
                if 'vendor' not in p and 'venv' not in p and 'cmake-build-debug' not in p:
                    with open(os.path.join(path, name), 'r') as file:
                        res[ext] = res.get(ext, 0) + len(file.readlines())

print('Lines of code:')
for i in res:
    print(f'.{i}: {res[i]}')
