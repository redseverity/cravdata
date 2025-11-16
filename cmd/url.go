/*
Copyright © 2025 redseverity <red.severity723@passfwd.com>
*/
package cmd

import (
	"github.com/redseverity/cravdata/cmd/docs/urldocs"
	"github.com/redseverity/cravdata/cmd/validators/urlverify"
	"github.com/spf13/cobra"
)

var (
	targetURL string
	marker    string
	charset   string
	min       int
	max       int
	timeout   int
	delay     int
)

// urlCmd represents the url subcommand
var urlCmd = &cobra.Command{
	Use:   urldocs.Use,
	Short: urldocs.Short,
	Long:  urldocs.Long,

	Args: func(cmd *cobra.Command, args []string) error {
		if err := cobra.MinimumNArgs(1)(cmd, args); err != nil {
			return err
		}

		targetURL = args[0]

		if err := urlverify.URL(targetURL); err != nil {
			return err
		}

		if err := urlverify.Marker(targetURL, marker); err != nil {
			return err
		}

		if err := urlverify.Charset(&charset); err != nil {
			return err
		}

		if err := urlverify.Min(min, max); err != nil {
			return err
		}

		if err := urlverify.Max(max, min); err != nil {
			return err
		}

		if err := urlverify.Timeout(timeout); err != nil {
			return err
		}

		if err := urlverify.Delay(delay); err != nil {
			return err
		}

		return nil
	},

	RunE: func(cmd *cobra.Command, args []string) error {
		return nil
	},
}

func init() {
	rootCmd.AddCommand(urlCmd)
	urlCmd.Flags().StringVarP(&marker, "marker", "m", "{BRUTE}", urldocs.Marker)
	urlCmd.Flags().StringVarP(&charset, "charset", "c", "abc", urldocs.Charset)
	urlCmd.Flags().IntVarP(&min, "min", "", 1, urldocs.Min)
	urlCmd.Flags().IntVarP(&max, "max", "", 3, urldocs.Max)
	urlCmd.Flags().IntVarP(&timeout, "timeout", "t", 2, urldocs.Timeout)
	urlCmd.Flags().IntVarP(&delay, "delay", "d", 0, urldocs.Delay)
}
