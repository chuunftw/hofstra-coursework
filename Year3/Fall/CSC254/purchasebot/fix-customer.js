const OrientDB = require('orientjs');

async function fixCustomer() {
  const server = OrientDB({
    host: "localhost",
    port: 2424,
    username: "root",
    password: "wigwomm",
    useToken: true
  });

  const db = server.use({
    name: "demodb",
    username: "root",
    password: "wigwomm"
  });

  try {
    console.log('Fixing malformed customer email...\n');

    // Update the customer with the correct email
    const result = await db.query(
      "UPDATE #260:0 SET email = 'lelouch@gmail.com'"
    ).all();

    console.log('Customer updated successfully!');
    console.log('Result:', result);

    // Verify the fix
    const customer = await db.query("SELECT FROM #260:0").all();
    console.log('\nVerified customer data:');
    console.log(`  Name: ${customer[0].name}`);
    console.log(`  Email: ${customer[0].email}`);

  } catch (err) {
    console.error("Error:", err.message);
  } finally {
    db.close();
    server.close();
  }
}

fixCustomer();
