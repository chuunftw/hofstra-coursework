const OrientDB = require('orientjs');

async function checkCustomers() {
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
    console.log('Attempting to fetch customers with timeout...\n');

    // Try to count customers first (this is faster)
    console.log('Step 1: Counting customers...');
    const countResult = await Promise.race([
      db.query("SELECT count(*) as count FROM Customer").all(),
      new Promise((_, reject) => setTimeout(() => reject(new Error('Timeout after 10 seconds')), 10000))
    ]);
    console.log(`Total Customers: ${countResult[0].count}\n`);

    // Try to fetch customers one by one
    console.log('Step 2: Fetching customer records...');
    const customers = await Promise.race([
      db.query("SELECT FROM Customer").all(),
      new Promise((_, reject) => setTimeout(() => reject(new Error('Timeout after 10 seconds')), 10000))
    ]);

    console.log(`Successfully fetched ${customers.length} customers:\n`);
    customers.forEach((customer, index) => {
      console.log(`${index + 1}. ${customer['@rid']}`);
      console.log(`   Name: ${customer.name || 'MISSING'}`);
      console.log(`   Email: ${customer.email || 'MISSING'}`);
      console.log(`   Phone: ${customer.phone || 'MISSING'}`);
      console.log(`   Address: ${customer.address || 'MISSING'}`);
      console.log();
    });

  } catch (err) {
    console.error("\nError occurred:", err.message);
    console.error("\nFull error:", err);

    // Try to query with LIMIT to see if we can get some records
    try {
      console.log("\nAttempting to fetch with LIMIT 10...");
      const limitedCustomers = await db.query("SELECT FROM Customer LIMIT 10").all();
      console.log(`Fetched ${limitedCustomers.length} customers with LIMIT`);
      limitedCustomers.forEach((customer, index) => {
        console.log(`${index + 1}. ${customer['@rid']} - ${customer.name} (${customer.email})`);
      });
    } catch (limitErr) {
      console.error("LIMIT query also failed:", limitErr.message);
    }
  } finally {
    db.close();
    server.close();
  }
}

checkCustomers();
