import ejs  from 'ejs';
import fs from 'fs';
import https from 'https';
import path from 'path';
import { fileURLToPath } from 'url';
const __dirname = path.dirname(fileURLToPath(import.meta.url));

function request(url, options) {
  return new Promise((resolve, reject) => {
    const req = https.request(url, options, (res) => {
      res.setEncoding('utf8');
      let responseBody = '';

      res.on('data', (chunk) => {
        responseBody += chunk;
      });

      res.on('end', () => {
        resolve(JSON.parse(responseBody));
      });
    });

    req.on('error', (err) => {
      reject(err);
    });

    req.end();
  });
}

function v_url(version) {
  const base_url = "https://digitalasset.jfrog.io/artifactory/api/storage/external-files/daml-enterprise";
  return base_url + "/" + version.split('.')[0] + '.' + version.split('.')[1] + "/" + version;
}

function d_url(version, file_name) {
  const base_url = "https://digitalasset.jfrog.io/artifactory/external-files/daml-enterprise";
  return base_url + "/" + version.split('.')[0] + '.' + version.split('.')[1] + "/" + version + "/" + file_name;
}

async function list(version) {
  const resp = await request(v_url(version),
                             {auth: process.env.ARTIFACTORY_USERNAME + ":" + process.env.ARTIFACTORY_PASSWORD});
  return resp.children.map((f) => f.uri.substring(1));
}

const components = [{name: "Daml SDK",
                     files: [{name: "Linux tar.gz", pattern: /^daml-sdk-.*-linux-ee\.tar\.gz$/},
                             {name: "macOS tar.gz", pattern: /^daml-sdk-.*-macos-ee\.tar\.gz$/},
                             {name: "Windows installer", pattern: /^daml-sdk-.*windows-ee\.exe$/}]},
                    {name: "Canton", files: [{name: "jar", pattern: /^canton-.*-ee\.jar$/}]},
                    {name: "Daml Finance", files: [{name: "tar.gz", pattern: /^daml-finance-.*-ee\.tar\.gz$/}]},
                    {name: "Daml Script", files: [{name: "jar", pattern: /^daml-script-.*-ee\.jar$/}]},
                    {name: "HTTP JSON API", files: [{name: "jar", pattern: /^http-json-.*-ee\.jar$/}]},
                    {name: "OAuth2 Middleware", files: [{name: "jar", pattern: /^oauth2-middleware-.*-ee\.jar$/}]},
                    {name: "Participant Query Store", files: [{name: "Scribe jar", pattern: /^participant-query-store-.*-ee\.jar$/}]},
                    {name: "Trigger Runner", files: [{name: "jar", pattern: /^trigger-runner-.*-ee\.jar$/}]},
                    {name: "Trigger Service", files: [{name: "jar", pattern: /^trigger-service-.*-ee\.jar$/}]}]

const index_template = fs.readFileSync('index.html.template', 'utf8');
const default_version = fs.readFileSync('../root', 'utf8').trim();
const data = await Promise.all(fs.readFileSync('../dropdown_versions', 'utf8')
                                 .split('\n')
                                 .slice(0, -1)
                                 .filter((v) => !v.startsWith("1."))
                                 .map(async (v) => {
  const all_files = await list(v);
  return {version: v,
          components: components.map((c) => {
            const files = c.files.map((f) => {
              const file = all_files.filter((af) => af.match(f.pattern));
              return {name: f.name,
                      url: d_url(v, file[0]),
                      signature: d_url(v, file[0] + ".asc")};
            });
            return {name: c.name, files};})};
}));

const index = ejs.render(index_template, {versions: data});

const output_dir = __dirname + '/out';

if (fs.existsSync(output_dir)) {
  fs.rmSync(output_dir, {recursive: true});
}

fs.mkdirSync(output_dir);
fs.writeFileSync(output_dir + '/index.html', index);
for (var static_file of ["downloads.css", "down.svg", "up.svg", "check.svg"]) {
  fs.copyFileSync(static_file, "out/" + static_file)
};
