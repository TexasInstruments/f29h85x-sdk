
const driverVer = {
    "hsmclient": {
        version: "v0",
    },
};

exports = {
    getDriverVer: function(driverName) {
        return driverVer[driverName].version;
    },
};
