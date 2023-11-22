const ejs = require('ejs');
const fs = require('fs');

const data = JSON.parse(fs.readFileSync('versions.json', 'utf8'));
const index_template = fs.readFileSync('index.html.template', 'utf8');
const version_template = fs.readFileSync('version.html.template', 'utf8');

const index = ejs.render(index_template, {versions: data});
const versions = data.map((v) => ({version: v.version,
                                   rendered: ejs.render(version_template, {v: v})}));

const output_dir = __dirname + '/out';

if (fs.existsSync(output_dir)) {
  fs.rmSync(output_dir, {recursive: true});
}

fs.mkdirSync(output_dir);
fs.writeFileSync(output_dir + '/index.html', index);
for (v of versions) {
  fs.writeFileSync(output_dir + "/" + v.version + ".html", v.rendered);
}
