from flask import Flask, render_template, request, redirect, url_for
import os

app = Flask(__name__)

# Function to read text files
def read_text_file(filename):
    file_path = os.path.join('static', filename)
    with open(file_path, 'r') as file:
        content = file.read()
    return content

# Function to write text files
def write_text_file(filename, content):
    file_path = os.path.join('static', filename)
    with open(file_path, 'w') as file:
        file.write(content)

@app.route('/')
def index():
    p1_content = read_text_file('p1.txt')
    p2_content = read_text_file('p2.txt')
    return render_template('index.html', p1=p1_content, p2=p2_content)

@app.route('/memory')
def memory():
    memory_content = read_text_file('output1.txt')
    return render_template('memory.html', memory=memory_content)

@app.route('/registers')
def registers():
    registers_content = read_text_file('output2.txt')
    return render_template('registers.html', registers=registers_content)

@app.route('/cpi')
def cpi():
    cpi_content = read_text_file('output3.txt')
    return render_template('cpi.html', cpi=cpi_content)

@app.route('/cache')
def cache():
    cache_content = read_text_file('output4.txt')
    return render_template('cache.html', cache=cache_content)

@app.route('/update_p1', methods=['POST'])
def update_p1():
    if request.method == 'POST':
        new_content = request.form['p1']
        write_text_file('p1.txt', new_content)
        return redirect(url_for('index'))

@app.route('/update_p2', methods=['POST'])
def update_p2():
    if request.method == 'POST':
        new_content = request.form['p2']
        write_text_file('p2.txt', new_content)
        return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)
