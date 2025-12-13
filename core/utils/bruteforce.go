package utils

import (
	"fmt"
	"strconv"
	"time"
)

func Bruteforce(url string, charset string, min int, max int, timeout int, delay int) {
	var generate func(prefix string, rest int)

	generate = func(prefix string, rest int) {

		if delay > 0 {
			time.Sleep(time.Duration(delay) * time.Millisecond)
		}

		if rest == 0 {
			request := Request(url+prefix, timeout)

			if !request.Verified {
				fmt.Printf(
					"[ERROR] %s %s\n",
					strconv.Itoa(request.Status)+":",
					request.URL,
				)
				return
			}

			fmt.Printf(
				"[SUCCESS] %s %s\n",
				strconv.Itoa(request.Status)+":",
				request.URL,
			)
			return
		}

		for i := 0; i < len(charset); i++ {
			generate(prefix+string(charset[i]), rest-1)
		}
	}

	for length := min; length <= max; length++ {
		generate("", length)
	}
}
