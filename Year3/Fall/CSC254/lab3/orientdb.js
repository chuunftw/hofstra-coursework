import orientjs from "orientjs"

let client = await orientjs.OrientDBClient.connect({
host: "localhost", port: 2424
})
let session = await client.session({name: "demodb",username: "admin", password:"admin"})

let result = await session.command("insert into Dessert set name = :name", {params: { name: "Tiramisu" }}).all()

let tiramisu = await session.query("select * from Dessert where name = :name", {params: {name: "Tiramisu"}}).all()
console.log(tiramisu)
await session.close()
await client.close()