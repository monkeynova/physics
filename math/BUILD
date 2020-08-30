cc_library(
    name = "quarternion",
    hdrs = ["quarternion.h"],
)

cc_test(
    name = "quarternion_test",
    srcs = ["quarternion_test.cc"],
    deps = [
        ":quarternion",
	"@com_monkeynova_gunit_main//:test_main",
        "@com_google_googletest//:gtest",
        "@com_google_absl//absl/strings",
    ],
)
